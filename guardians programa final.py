import cv2
import serial
import time
from deepface import DeepFace
import mediapipe as mp
import numpy as np
import threading
import pygame
import sys
import os

# Camera capture
cap = cv2.VideoCapture(0)

pygame.init()
pygame.mixer.init()

# Audio control variables
current_music = None
current_narrator = None
audio_playing = False
audio_thread = None

# Define audio files for each state
audio_configuration = {
    "background": {
        "music": "inside out1.mp3",
        "narrator": None
    },
    "open_hand": {
        "narrator": "",
        "message": "Detectando ansiedad...."
    },
    "anger": {
        "narrator": "anger-audio2.wav",
        "message": "Furia detectada..."
    },
    "sadness": {
        "narrator": "sadness-sound.wav",
        "message": "Tristeza detectada...."
    },
    "happiness": {
        "narrator": "joy-sound.wav",
        "message": "Alegría detectada..."
    },
    "surprise": {
        "narrator": "C:/Users/Home/PycharmProjects/PythonProject/sorpresa_narrator.mp3",
        "message": "Sorpresa detectada..."
    },
    "closed_hand": {
        "narrator": "C:/Users/Home/PycharmProjects/PythonProject/final_narrator.mp3",
        "message": "Secuencia completada..."
    }
}

try:
    pygame.mixer.music.load(audio_configuration["background"]["music"])
    pygame.mixer.music.set_volume(0.7) 
    pygame.mixer.music.play(loops=-1)
    current_music = "background"
    print("Playing background music in loop.")
except Exception as e:
    print(f"Error loading background music: {e}")

# Create a clock to limit CPU usage
clock = pygame.time.Clock()

# Initialize Arduino communication
try:
    arduino = serial.Serial('COM16', 9600)
    print("Connected to Arduino")
except:
    arduino = None
    print("Arduino not connected")

# Complete MediaPipe initialization
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mp_face_mesh = mp.solutions.face_mesh
mp_face_detection = mp.solutions.face_detection
mp_hands = mp.solutions.hands

# Face Mesh configuration
face_mesh = mp_face_mesh.FaceMesh(
    max_num_faces=1,
    refine_landmarks=True,
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5
)

face_detection = mp_face_detection.FaceDetection(min_detection_confidence=0.5)

# Hand detection configuration
hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=1,
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5
)

# CORRECTED STATE FLOW
flow_states = [
    "open_hand",  # 0: Buscar mano abierta
    "anger",      # 1: Buscar furia
    "sadness",    # 2: Buscar tristeza
    "happiness",  # 3: Buscar alegría
    "surprise",   # 4: Buscar sorpresa
    "closed_hand", # 5: Buscar mano cerrada
    "finished"    # 6: Estado final
]

# Flow control variables
current_state_index = 0
current_state = flow_states[current_state_index]
signal_sent = False
counter = 0
STABILITY_THRESHOLD = 2  # Reducido para mayor sensibilidad
delay_start = None
next_emotion = None
state_completed = False

# DELAY between states (INCREASED TO 7 SECONDS)
DELAY_BETWEEN_STATES = 7

# Emotion detection thresholds
EMOTION_CONFIDENCE_THRESHOLD = 40  # Mínimo de confianza para detectar emoción
SAD_THRESHOLD_BOOST = 0.30
SURPRISE_THRESHOLD_BOOST = 0.50

# Video configuration for each state
state_configuration = {
    "open_hand": {
        "video": "ansiedad.mp4",
        "letter": "A",
        "message": "Open hand detected - Starting sequence"
    },
    "anger": {
        "video": "furia.mp4",
        "letter": "B",
        "message": "Anger detected"
    },
    "sadness": {
        "video": "tristeza.mp4",
        "letter": "C",
        "message": "Sadness detected"
    },
    "happiness": {
        "video": "alegria.mp4",
        "letter": "D",
        "message": "Happiness detected"
    },
    "surprise": {
        "video": "todos.mp4",
        "letter": "E",
        "message": "Surprise detected"
    },
    "closed_hand": {
        "video": "final.mp4",
        "letter": "F",
        "message": "Closed hand detected - Sequence completed"
    }
}

# Colors for different emotions (BGR)
emotion_colors = {
    'happy': (0, 255, 255),     # Yellow
    'sad': (255, 0, 0),         # Blue
    'angry': (0, 0, 255),       # Red
    'surprise': (0, 255, 0),    # Green
    'neutral': (255, 255, 255),
    'hand_open': (0, 255, 255),  # Cyan for open hand
    'hand_closed': (255, 0, 255) # Magenta for closed hand
}

# Video playback variables
video_playing = False
video_thread = None

# Audio control functions
def stop_all_audio():
    """Stop all audio playback"""
    global audio_playing, audio_thread
    try:
        pygame.mixer.music.stop()
        if audio_playing and audio_thread and audio_thread.is_alive():
            audio_playing = False
            audio_thread.join(timeout=1.0)
        print("All audio stopped")
    except Exception as e:
        print(f"Error stopping audio: {e}")

def change_background_music(music_file, volume=0.7):
    """Change background music with volume control"""
    global current_music
    try:
        if os.path.exists(music_file):
            pygame.mixer.music.load(music_file)
            pygame.mixer.music.set_volume(volume)
            pygame.mixer.music.play(loops=-1)
            current_music = music_file
            print(f"Background music changed to: {music_file} at volume {volume}")
        else:
            print(f"Music file not found: {music_file}")
    except Exception as e:
        print(f"Error changing background music: {e}")

def play_emotion_audio(state):
    """Play complete audio sequence with proper mixing"""
    global current_music
    
    if state not in audio_configuration:
        print(f"No audio configuration for state: {state}")
        return

    config = audio_configuration[state]

    def audio_sequence():
        try:
            if pygame.mixer.music.get_busy():
                pygame.mixer.music.set_volume(0.2)
                print("Background music volume lowered for narrator")

            if config["narrator"] and os.path.exists(config["narrator"]):
                print(f"Playing narrator for {state}: {config['message']}")
                narrator_sound = pygame.mixer.Sound(config["narrator"])
                narrator_sound.set_volume(1.0)
                narrator_channel = narrator_sound.play()
                
                while narrator_channel.get_busy():
                    pygame.time.wait(100)
                
                print("Narrator finished")
                time.sleep(0.5)

            if config.get("music") and os.path.exists(config["music"]):
                change_background_music(config["music"], volume=0.7)
            else:
                pygame.mixer.music.set_volume(0.7)
                print("Restored background music volume")

        except Exception as e:
            print(f"Error in audio sequence for {state}: {e}")
            if pygame.mixer.music.get_busy():
                pygame.mixer.music.set_volume(0.7)

    audio_thread = threading.Thread(target=audio_sequence)
    audio_thread.daemon = True
    audio_thread.start()

def return_to_background_music():
    """Return to original background music"""
    global current_music
    if current_music != "background":
        try:
            change_background_music(audio_configuration["background"]["music"], volume=0.7)
            current_music = "background"
            print("Returned to background music")
        except Exception as e:
            print(f"Error returning to background music: {e}")

# Gesture detection functions
def is_open_hand(landmarks):
    """Detect if hand is open"""
    try:
        tip_ids = [4, 8, 12, 16, 20]
        pip_ids = [3, 6, 10, 14, 18]
        fingers_up = 0

        for i in range(5):
            if i == 0:  # Thumb
                if landmarks.landmark[tip_ids[i]].x > landmarks.landmark[pip_ids[i]].x:
                    fingers_up += 1
            else:  # Other fingers
                if landmarks.landmark[tip_ids[i]].y < landmarks.landmark[pip_ids[i]].y:
                    fingers_up += 1

        return fingers_up >= 4
    except:
        return False

def is_closed_hand(landmarks):
    """Detect if hand is closed (fist)"""
    try:
        tip_ids = [4, 8, 12, 16, 20]
        pip_ids = [3, 6, 10, 14, 18]
        fingers_up = 0

        for i in range(5):
            if i == 0:  # Thumb
                if landmarks.landmark[tip_ids[i]].x > landmarks.landmark[pip_ids[i]].x:
                    fingers_up += 1
            else:  # Other fingers
                if landmarks.landmark[tip_ids[i]].y < landmarks.landmark[pip_ids[i]].y:
                    fingers_up += 1

        return fingers_up <= 1
    except:
        return False

# Video playback functions
def play_video(video_path):
    """Play video in separate thread"""
    global video_playing
    video_playing = True

    try:
        video = cv2.VideoCapture(video_path)
        if not video.isOpened():
            print(f"Error: could not open video --> {video_path}")
            video_playing = False
            return

        print(f"Playing video: {video_path}")

        while video.isOpened() and video_playing:
            ret, frame = video.read()
            if not ret:
                break

            if frame.shape[0] > 800:
                scale_percent = 800 / frame.shape[0]
                width = int(frame.shape[1] * scale_percent)
                height = int(frame.shape[0] * scale_percent)
                frame = cv2.resize(frame, (width, height))

            cv2.imshow("Video", frame)
            if cv2.waitKey(25) & 0xFF == ord('q'):
                break

        video.release()
        cv2.destroyWindow("Video")
    except Exception as e:
        print(f"An error occurred while playing video: {e}")
    finally:
        video_playing = False

def start_video(video_path):
    """Start video playback"""
    global video_thread, video_playing
    stop_current_video()
    video_thread = threading.Thread(target=play_video, args=(video_path,))
    video_thread.daemon = True
    video_thread.start()

def stop_current_video():
    """Stop current video"""
    global video_playing, video_thread
    if video_playing and video_thread and video_thread.is_alive():
        video_playing = False
        video_thread.join(timeout=1.0)

def draw_custom_mesh(image, landmarks, emotion):
    """Draw custom facial mesh"""
    h, w, c = image.shape
    color = emotion_colors.get(emotion, (0, 255, 0))
    connections = mp_face_mesh.FACEMESH_TESSELATION
    overlay = image.copy()

    for connection in connections:
        start_idx = connection[0]
        end_idx = connection[1]
        start_point = landmarks.landmark[start_idx]
        end_point = landmarks.landmark[end_idx]
        start_x = int(start_point.x * w)
        start_y = int(start_point.y * h)
        end_x = int(end_point.x * w)
        end_y = int(end_point.y * h)
        cv2.line(overlay, (start_x, start_y), (end_x, end_y), color, 1)

    alpha = 0.4
    cv2.addWeighted(overlay, alpha, image, 1 - alpha, 0, image)
    return image

def adjust_emotion_values(emotion_data, target_emotion):
    """Adjust emotion values to boost target emotion"""
    if not emotion_data or 'emotion' not in emotion_data:
        return emotion_data

    adjusted = emotion_data.copy()

    if target_emotion == "sadness":
        sad_value = adjusted['emotion']['sad']
        sad_value = min(100, sad_value * (1 + SAD_THRESHOLD_BOOST))
        adjusted['emotion']['sad'] = sad_value
    elif target_emotion == "surprise":
        surprise_value = adjusted['emotion']['surprise']
        surprise_value = min(100, surprise_value * (1 + SURPRISE_THRESHOLD_BOOST))
        adjusted['emotion']['surprise'] = surprise_value

    max_emotion = max(adjusted['emotion'], key=adjusted['emotion'].get)
    adjusted['dominant_emotion'] = max_emotion
    return adjusted

def advance_state():
    """Advance to next state in the flow"""
    global current_state_index, current_state, signal_sent, counter, delay_start, next_emotion, state_completed

    if current_state_index < len(flow_states) - 1:
        current_state_index += 1
        current_state = flow_states[current_state_index]
        signal_sent = False
        counter = 0
        next_emotion = None
        state_completed = False
        delay_start = time.time()  # Inicia el delay

        print(f"\n=== ADVANCING TO STATE: {current_state.upper()} ===")
        print(f"Waiting {DELAY_BETWEEN_STATES} seconds before detecting...")
        
        return_to_background_music()
    else:
        print("Sequence completed!")

def reset_detection_state():
    """Reset detection counters when detection fails"""
    global counter, next_emotion
    if counter > 0:
        counter = max(0, counter - 1)
    next_emotion = None

def process_detection(detection_type):
    """Process when something is detected (emotion or gesture)"""
    global counter, signal_sent, state_completed

    config = state_configuration.get(current_state)
    if not config:
        return

    # Check delay period
    if delay_start and current_state_index > 0:
        elapsed_time = time.time() - delay_start
        if elapsed_time < DELAY_BETWEEN_STATES:
            remaining_time = DELAY_BETWEEN_STATES - elapsed_time
            print(f"Still in delay period. Remaining: {remaining_time:.1f} seconds")
            return

    counter += 1
    print(f"Detection stability for {current_state}: {counter}/{STABILITY_THRESHOLD}")

    if counter >= STABILITY_THRESHOLD and not signal_sent:
        print(f"\n*** DETECTION CONFIRMED: {config['letter']} - {config['message']} ***")

        if arduino:
            try:
                arduino.write(str.encode(config['letter']))
                print(f"Signal sent to Arduino: {config['letter']}")
            except Exception as e:
                print(f"Error sending to Arduino: {e}")

        play_emotion_audio(current_state)

        if 'video' in config:
            start_video(config['video'])

        signal_sent = True
        state_completed = True

        # Advance to next state after delay (increased to 7 seconds)
        print(f"Advancing to next state in 7 seconds...")
        threading.Timer(7.0, advance_state).start()

def create_info_panel(image, emotion_data, hand_detected, hand_type):
    """Create complete information panel"""
    h, w, c = image.shape
    panel = np.zeros((250, w, 3), dtype=np.uint8)

    cv2.putText(panel, "Emotion & Gesture Recognition System", (10, 25),
                cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 2)

    state_display = current_state.replace("_", " ").upper()
    cv2.putText(panel, f"Current State: {state_display}", (10, 50),
                cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 255), 2)

    progress = f"Step {current_state_index + 1} of {len(flow_states) - 1}"
    cv2.putText(panel, progress, (10, 75),
                cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 2)

    # Delay information
    if delay_start and current_state_index > 0:
        elapsed_time = time.time() - delay_start
        if elapsed_time < DELAY_BETWEEN_STATES:
            remaining_time = DELAY_BETWEEN_STATES - elapsed_time
            cv2.putText(panel, f"Delay: {remaining_time:.1f} sec remaining", (10, 100),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 0), 2)
        else:
            cv2.putText(panel, "Ready for detection", (10, 100),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
    else:
        cv2.putText(panel, "Ready for detection", (10, 100),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)

    # Detection status
    if current_state in ["open_hand", "closed_hand"]:
        if hand_detected:
            cv2.putText(panel, f"Hand Detected: {hand_type.upper()}", (10, 125),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
        else:
            cv2.putText(panel, f"Searching for: {current_state.replace('_', ' ')}", (10, 125),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 255), 2)
    elif current_state in ["anger", "sadness", "happiness", "surprise"]:
        if emotion_data:
            dominant_emotion = emotion_data['dominant_emotion']
            confidence = emotion_data['emotion'][dominant_emotion]
            color = emotion_colors.get(dominant_emotion, (255, 255, 255))
            cv2.putText(panel, f"Detected: {dominant_emotion.upper()} ({confidence:.1f}%)", (10, 125),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6, color, 2)
        else:
            cv2.putText(panel, f"Searching for: {current_state.upper()}", (10, 125),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 255), 2)

    # Stability counter
    if signal_sent:
        cv2.putText(panel, "Signal Sent ✓", (10, 150),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
    else:
        cv2.putText(panel, f"Stability: {counter}/{STABILITY_THRESHOLD}", (10, 150),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 2)

    result = np.vstack([image, panel])
    return result

# Main program
program_running = True
print(f"Starting system in state: {current_state}")
print("Show an open hand to begin the sequence...")

while cap.isOpened() and program_running:
    ret, frame = cap.read()
    if not ret:
        break

    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    
    emotion_data = None
    hand_detected = False
    hand_type = "none"

    # Check if we can detect (after delay)
    can_detect = True
    if delay_start and current_state_index > 0:
        elapsed_time = time.time() - delay_start
        can_detect = elapsed_time >= DELAY_BETWEEN_STATES

    if not signal_sent and can_detect:  # Solo detectar si no se ha enviado señal y no hay delay
        
        if current_state in ["open_hand", "closed_hand"]:
            # Detect hand gestures
            results_hands = hands.process(rgb_frame)

            if results_hands.multi_hand_landmarks:
                hand_detected = True
                hand_landmarks = results_hands.multi_hand_landmarks[0]

                mp_drawing.draw_landmarks(
                    frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

                if current_state == "open_hand" and is_open_hand(hand_landmarks):
                    hand_type = "open"
                    process_detection("open_hand")
                elif current_state == "closed_hand" and is_closed_hand(hand_landmarks):
                    hand_type = "closed"
                    process_detection("closed_hand")
                else:
                    reset_detection_state()
            else:
                reset_detection_state()

        elif current_state in ["anger", "sadness", "happiness", "surprise"]:
            # Detect faces and emotions
            results_mesh = face_mesh.process(rgb_frame)

            if results_mesh.multi_face_landmarks:
                try:
                    result = DeepFace.analyze(frame, actions=['emotion'], enforce_detection=False)
                    if result:
                        emotion_data = result[0]
                        emotion_data = adjust_emotion_values(emotion_data, current_state)
                        dominant_emotion = emotion_data['dominant_emotion']
                        confidence = emotion_data['emotion'][dominant_emotion]

                        frame = draw_custom_mesh(frame, results_mesh.multi_face_landmarks[0], dominant_emotion)

                        target_emotions = {
                            "anger": "angry",
                            "sadness": "sad", 
                            "happiness": "happy",
                            "surprise": "surprise"
                        }

                        target_emotion = target_emotions.get(current_state)
                        
                        if (dominant_emotion == target_emotion and 
                            confidence >= EMOTION_CONFIDENCE_THRESHOLD):
                            
                            if next_emotion == dominant_emotion:
                                # La misma emoción detectada consecutivamente
                                process_detection(dominant_emotion)
                            else:
                                # Nueva emoción detectada, reiniciar contador
                                counter = 1
                                next_emotion = dominant_emotion
                                print(f"New emotion detected: {dominant_emotion} ({confidence:.1f}%)")
                        else:
                            # Emoción no coincide o confianza baja
                            reset_detection_state()

                except Exception as e:
                    print(f"Error analyzing emotion: {e}")
                    reset_detection_state()
            else:
                reset_detection_state()

    elif current_state == "finished":
        cv2.putText(frame, "SEQUENCE COMPLETED!", (50, 50),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 3)

    # Create and show information panel
    result_frame = create_info_panel(frame, emotion_data, hand_detected, hand_type)

    if result_frame.shape[0] > 900:
        scale_percent = 900 / result_frame.shape[0]
        width = int(result_frame.shape[1] * scale_percent)
        height = int(result_frame.shape[0] * scale_percent)
        result_frame = cv2.resize(result_frame, (width, height))

    cv2.imshow("Recognition System", result_frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        program_running = False
        break

# Cleanup
stop_current_video()
stop_all_audio()
cap.release()
cv2.destroyAllWindows()

if arduino:
    arduino.close()

pygame.mixer.music.stop()
pygame.quit()

print("Program finished")