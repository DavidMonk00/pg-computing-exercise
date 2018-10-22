#include "TrackerStatistics.hpp"

void* threadCallBack(void* tp) {
  ThreadParams* t = (ThreadParams*)tp;
  long id = t->id;
  int concurentThreadsSupported = t->concurentThreadsSupported;
  int start = TOTAL_TRACKS * id/concurentThreadsSupported;
  int end = TOTAL_TRACKS * (id + 1)/concurentThreadsSupported;
  std::cout << "Thread ID=" << id << " " << start << " " << end << '\n';
  track_params* track_parameters = t->track_parameters;
  Track** tracks = t->tracks;
  int i, c=0;
  for (i = start; i < end; i++,c++) {
    tracks[i]->fit(track_parameters, i);
  }
  std::cout << c << '\n';
  pthread_exit(NULL);
}

TrackerStatistics::TrackerStatistics() {
  std::srand(std::time(NULL));
  concurentThreadsSupported = 1;//std::thread::hardware_concurrency();
  std::cout << "Available threads: " << concurentThreadsSupported << '\n';
}

TrackerStatistics::~TrackerStatistics() {
  for (int i = 0; i < TOTAL_TRACKS; i++) {
    delete tracks[i];
  }
  free(tracks);
  free(track_parameters);
}

void TrackerStatistics::readFile(std::string filename) {
  std::streampos size;
  std::ifstream file(filename, std::ios::in|std::ios::binary|std::ios::ate);
  if (file.is_open()) {
    //size = file.tellg();
    //std::cout << (size == TOTAL_TRACKS*TRACK_SIZE) << '\n';
    file.seekg (0,std::ios::beg);
    tracks = (Track**)malloc(TOTAL_TRACKS*sizeof(Track*));
    bytes = (char*)malloc(TOTAL_TRACKS*TRACK_SIZE*sizeof(char));
    file.read(bytes, TOTAL_TRACKS*TRACK_SIZE);
    char track[TRACK_SIZE];
    for (int i = 0; i < TOTAL_TRACKS; i++) {
      tracks[i] = new Track(&bytes[i*TRACK_SIZE]);
    }
    file.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
}

void TrackerStatistics::fit() {
  track_parameters = (track_params*)malloc(TOTAL_TRACKS*sizeof(track_params));
  pthread_t thread[concurentThreadsSupported];
  int rc;
  long t;
  void *status;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  std::vector<std::thread> threads;
  if (TOTAL_TRACKS > concurentThreadsSupported) {
    for (t = 0; t < concurentThreadsSupported; t++) {
      ThreadParams* tp = new ThreadParams;
      tp->tracks = tracks;
      tp->track_parameters = track_parameters;
      tp->concurentThreadsSupported = concurentThreadsSupported;
      tp->id = t;
      rc = pthread_create(&thread[t], &attr, threadCallBack, (void *)tp);
      if (rc) {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
    }
    pthread_attr_destroy(&attr);
    for (t = 0; t < concurentThreadsSupported; t++) {
      rc = pthread_join(thread[t], &status);
      if (rc) {
         printf("ERROR; return code from pthread_join() is %d\n", rc);
         exit(-1);
      }
    }
  } else {
    ThreadParams* tp = new ThreadParams;
    tp->tracks = tracks;
    tp->track_parameters = track_parameters;
    tp->concurentThreadsSupported = 1;
    tp->id = 0;
    threads.push_back(std::thread(threadCallBack, (void*)tp));
  }
}

void TrackerStatistics::getStats() {
  float g_mean = 0;
  float v_mean = 0;
  for (int i = 0; i < TOTAL_TRACKS; i++) {
    g_mean += track_parameters[i].gradient;
    v_mean += track_parameters[i].v;
  }
  std::cout << g_mean/TOTAL_TRACKS << " " << v_mean/TOTAL_TRACKS << '\n';
}

void TrackerStatistics::saveData(std::string filename) {
  std::ofstream myfile (filename);
  if (myfile.is_open()) {
    for (int i = 0; i < TOTAL_TRACKS; i++) {
      myfile << track_parameters[i].gradient << ",";
      myfile << track_parameters[i].v << "\n";
    }
    myfile.close();
  }
  else std::cout << "Unable to open file";
}
