#include <csignal>
#include <ctime>
#include <cstring>

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "md_config.hpp"

using namespace std;

#define MAX_FILENAME_LENGTH 256
#define MAX_BUFFER_SIZE 20
#define CAMERA_INDEX 0
#define MIN_CONTOUR_AERA 250


/* start function signature */
bool detect_motion(const myMat, myMat&, const double,
                   const cv::Ptr<cv::BackgroundSubtractorMOG2>);
size_t get_filename(char*, const char*, const char*, const char*, const char*);
void save_video(const char*, cv::VideoWriter&, myMat);
void joinFrames(const myMat, const myMat, myMat&);
/* end function signature */


/* const variables */
const char* const_str_data_format = "%m%d%y_%H%M%S";
const int const_record_duration_sec = 20;
const char* output_folder = "/mnt/syba/SambaShare/mjpg_streamer_pics/";
//const char* output_folder = "./";
const char* filename_prefix = "fullsize_";
const char* picture_ext = ".png";
const char* video_ext = ".avi";
/* end const variables */

/*********************************************
 * Start Main
 *********************************************/
int main(int argc, char* argv[])
{
  // open the camera
  cv::VideoCapture cam = cv::VideoCapture(CAMERA_INDEX);
  if (!cam.isOpened()) {
    cout << "Cannot open camera " << CAMERA_INDEX << endl;
    return EXIT_FAILURE;
  }
  
  // define variables for loop
  myMat frame, resized_frame, mesh_frame;
  cv::Size s;
  cv::Ptr<cv::BackgroundSubtractorMOG2> mog2 = 
    cv::createBackgroundSubtractorMOG2();
  
  bool isRecording = false;
  
  time_t cur_rawtime, rec_rawtime, delta_rawtime;
  time(&cur_rawtime); // initialize with current time
  time(&rec_rawtime); // initialize with current time
  struct tm* timeinfo;
  
  char formated_time_str[MAX_BUFFER_SIZE];
  char fullsize_filename[MAX_FILENAME_LENGTH];
  char video_filename[MAX_FILENAME_LENGTH];
  cv::VideoWriter outputVideo;
    
  // process wach frame
  for (size_t i=0;;i++) {
    cam >> frame;
    if (s.area() == 0)
      s = frame.size() / 3; // faster process time with smaller frame
    cv::resize(frame, resized_frame, s);

    my_imshow("Full", frame);
    my_imshow("Small", resized_frame);

    // check if there is movement, if yes, take a picture and start recording
    bool isMotionDetected = detect_motion(resized_frame,
                                          mesh_frame,
                                          MIN_CONTOUR_AERA, mog2);
    if(isMotionDetected && !isRecording) {
      // get current timestamp
      time(&rec_rawtime);
      timeinfo = localtime(&rec_rawtime);
      strftime(formated_time_str, MAX_BUFFER_SIZE,
               const_str_data_format, timeinfo);
      
      cout << "Motion detected" << endl;
    
      // save resized frame and mesh frame together
      myMat combined_frame(s.height, 2*s.width, resized_frame.type());
      get_filename(fullsize_filename, output_folder, 
                   filename_prefix, formated_time_str, picture_ext);
      cout << "Saving image to " << fullsize_filename << endl;
      joinFrames(resized_frame.clone(), mesh_frame.clone(), combined_frame);
      cv::imwrite(fullsize_filename, combined_frame);
      
      isRecording = true;
    }
    
    // record X second video if motion is detected
    time(&cur_rawtime);
    delta_rawtime = difftime(cur_rawtime, rec_rawtime);
    isRecording = (delta_rawtime>=0 && delta_rawtime<=const_record_duration_sec);
    if(isRecording) {
      get_filename(video_filename, output_folder, 
                   filename_prefix, formated_time_str, video_ext);
      save_video(video_filename, outputVideo, frame);
    }
    else if (!isRecording && outputVideo.isOpened()) {
      outputVideo.release();  // release the pointer
    }

    // TODO: replace with signal(SIGKILL)
#if SHOW_WINDOWS
    if ((cv::waitKey(1) & 0xFF) == 'q')
      break;
#endif // USE_OPENCL

  }

  // Clean up
  cam.release();
  return EXIT_SUCCESS;
}
/*********************************************
* End Main
*********************************************/

/*
 * Using background subtractor to detect movement
 */
bool detect_motion(const myMat input_frame, myMat& output_frame,
                   const double contour_area,
                   const cv::Ptr<cv::BackgroundSubtractorMOG2> ptr_bgsubtractor) {
  ptr_bgsubtractor->apply(input_frame, output_frame);

  vector<myMat> contours;
  cv::findContours(output_frame.clone(), contours, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_SIMPLE);
  for (int i = 0; i<contours.size(); i++) {
    if (cv::contourArea(contours[i]) < contour_area) {
      continue;
    }
    return true;
  }
  return false;
}

/*
 * Generate a filename
 */
size_t get_filename(char* filename, const char* path2dir, 
                    const char* basename, const char* timestamp,
                    const char* ext) {
  size_t i, j, k, l, m;
  i = strlen(path2dir);
  j = strlen(basename);
  k = strlen(timestamp);
  l = strlen(ext);
  m = i+j+k+l+1;
  
  strcpy(filename, path2dir);
  strcpy(filename+i, basename);
  strcpy(filename+i+j, timestamp);
  strcpy(filename+i+j+k, ext);
  
  filename[m] = '\0';
  return m;
}

/*
 * Save frame to video
 */
void save_video(const char* filename, cv::VideoWriter& VideoWriter, myMat frame) {
  if(!VideoWriter.isOpened()) {
    bool success = VideoWriter.open(filename,
		                                cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                                    10, frame.size(), true);
  }
  cv::Mat tmp_frame;
  frame.copyTo(tmp_frame);
  VideoWriter << tmp_frame; // VideoWrite accept cv::Mat only
}

/*
 * Combine 2 frames into 1
 */
void joinFrames(const myMat left_frame, 
                const myMat right_frame,
                myMat& combined_frame) {
  cv::Size left_size = left_frame.size();
  cv::Size right_size = right_frame.size();

  myMat converted_right_frame;
  cv::cvtColor(right_frame, converted_right_frame, cv::COLOR_GRAY2BGR);

  combined_frame.adjustROI(0, 0, 0, -right_size.width);
  left_frame.copyTo(combined_frame);
  combined_frame.adjustROI(0, 0, -left_size.width, right_size.width);
  converted_right_frame.copyTo(combined_frame);
  combined_frame.adjustROI(0, 0, left_size.width, 0);

  my_imshow("Combined", combined_frame);
}
