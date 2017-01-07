import cv2

CAM_INDEX = 0
MIN_DETECT_AERA = 500
FRAME_THRESHOLD = 25

cam = cv2.VideoCapture(CAM_INDEX)
backgroundFrame = None

while True:
  # get frame
  (grabbed, frame) = cam.read()
  if not grabbed:
    break
  
  # processing
  gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
  gray = cv2.GaussianBlur(gray, (21, 21), 0)
  if backgroundFrame is None:
    backgroundFrame = gray
    continue
  
  frameDelta = cv2.absdiff(backgroundFrame, gray)
  thresh = cv2.threshold(frameDelta, 
                         FRAME_THRESHOLD, 
                         255, 
                         cv2.THRESH_BINARY)[1] # need frame only
  
  thresh = cv2.dilate(thresh, None, iterations=2)
  (_, cnts, _) = cv2.findContours(thresh.copy(),
                               cv2.RETR_EXTERNAL,
		                           cv2.CHAIN_APPROX_SIMPLE)
  
  # draw a rectangle around the detected movement
  for c in cnts:
    if cv2.contourArea(c) < MIN_DETECT_AERA:
      continue
    (x, y, w, h) = cv2.boundingRect(c)
    cv2.rectangle(frame,
                  (x, y),
                  (x + w, y + h),
                  (0, 255, 0),
                  2)
  
  # show result
  cv2.imshow('Security Feed', frame)
  cv2.imshow('Thresh', thresh)
  #cv2.imshow('Frame Delta', frameDelta)
  
  if (cv2.waitKey(1) & 0xFF) == ord('q'):
    break
    
cam.release()
cv2.destroyAllWindows()