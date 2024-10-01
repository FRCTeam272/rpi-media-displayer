import yt_dlp
import requests
import os
import cv2
import time

import pygame
import threading

class Video:
    def __init__(self, name: str, url: str, is_downloaded=False, is_requested=False, video_location=''):
        self.name = name
        self.url = url
        self.is_downloaded = is_downloaded
        self.is_requested = is_requested
        self.video_location = video_location

def download_video(video: Video):
    ydl_opts = {
        'outtmpl': os.path.join('./videos', f'{video.name}.%(ext)s'),
        'format': 'bestvideo+bestaudio/best',  # Select the best video and best audio format
    }

    with yt_dlp.YoutubeDL(ydl_opts) as ydl:
        ydl.download([video.url])

def play_audio(audio_path):
    pygame.mixer.init()
    pygame.mixer.music.load(audio_path)
    pygame.mixer.music.play()
    
    while pygame.mixer.music.get_busy():
        pygame.time.Clock().tick(10)

def play_video(video_path):
    cap = cv2.VideoCapture(video_path)
    
    if not cap.isOpened():
        print("Error: Could not open video.")
        return

    # Extract audio from video
    audio_path = 'temp_audio.wav'
    if os.path.exists(audio_path):
        os.remove(audio_path)
    os.system(f'ffmpeg -i "{video_path}" -q:a 0 -map a {audio_path}')

    # Start a separate thread to play audio
    audio_thread = threading.Thread(target=play_audio, args=(audio_path,))
    audio_thread.start()
    
    # Create a named window
    cv2.namedWindow('Video', cv2.WND_PROP_FULLSCREEN)

    # Set the window to full screen
    cv2.setWindowProperty('Video', cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        cv2.imshow('Video', frame)

        # Press 'q' to exit the video
        if cv2.waitKey(25) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

    # Wait for the audio thread to finish
    audio_thread.join()

    # Remove the temporary audio file
    os.remove(audio_path)


videos = set()

# main video loop
while True:
    if not os.path.exists('./videos'):
        os.makedirs('./videos')

    # get the existing files first
    for file in os.listdir('./videos'):
        print(file)
        videos.add(Video(file.split('.')[0], '', is_downloaded=True, video_location=f'./videos/{file}'))
        
    # get the requested videos
    response = requests.get('https://raw.githubusercontent.com/FRCTeam272/rpi-media-displayer/refs/heads/main/data.csv')
    for line in response.text.split('\n'):
        if line == '':
            continue
        name, url = line.split(',')
        if not any(video.name == name for video in videos):
            videos.add(Video(name, url, is_requested=True, is_downloaded=False))
        else:
            for video in videos:
                if video.name == name:
                    video.url = url
                    video.is_requested = True

    for video in videos:
        if video.is_requested and not video.is_downloaded:
            print(f'Downloading {video.name}...')
            download_video(video)
        if video.is_downloaded and not video.is_requested:
            print(f'{video.name} is already downloaded and not requested. Deleting...')
            os.remove(f'./videos/{video.name}.mp4')
        if video.is_downloaded and video.is_requested:
            print(f'{video.name} is already downloaded and requested. Skipping...')

    for video in videos:
        # play the video
        time.sleep(3)
        video_path = f'{video.video_location}'
        play_video(video_path)
        