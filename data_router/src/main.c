#include <pthread.h>

#include "workers.h"

int main() {
    pthread_t sensor_worker_id;;
    pthread_create(&sensor_worker_id, NULL, sensor_read_worker, NULL);
    pthread_t file_worker_id;
    pthread_create(&file_worker_id, NULL, file_worker, NULL);
    pthread_t stream_worker_id;;
    pthread_create(&stream_worker_id, NULL, realtime_stream_worker, NULL);
    pthread_t command_worker_id;;
    pthread_create(&command_worker_id, NULL, command_worker, NULL);
    printf("[MAIN  ] Started all workers.\n");

    pthread_join(sensor_worker_id, NULL);
    pthread_join(file_worker_id, NULL);
    // This worker might hang waiting for connections, we should manually
    // cancel it.
    pthread_cancel(stream_worker_id);
    pthread_join(stream_worker_id, NULL);
    // Same thing here.
    pthread_cancel(command_worker_id);
    pthread_join(command_worker_id, NULL);
    printf("[MAIN  ] All workers shut down successfully.\n");
}
