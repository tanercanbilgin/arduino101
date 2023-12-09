import cv2
import serial

arduino = serial.Serial('COM3', 9600)  

face_classifier = cv2.CascadeClassifier('data/haarcascade_frontalface_default.xml')

def detectFaces(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_classifier.detectMultiScale(gray, 1.3, 5)
    if len(faces) == 0:
        arduino.write(b'R')
        return img
    for (x,y,w,h) in faces:
        cv2.rectangle(img, (x,y), (x+w,y+h), (255,0,0), 2)
        arduino.write(b'G')
    return img

cap = cv2.VideoCapture(1)

while True:
    ret, frame = cap.read()
    frame = detectFaces(frame)
    cv2.imshow('Face Detection', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break