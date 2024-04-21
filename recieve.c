#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* sender_thread(void* arg) {
    char* ip_address = (char*)arg;
    char command[256];
    sprintf(command, "gst-launch-1.0 v4l2src ! videoconvert ! x264enc ! queue max-size-time=10000000000 ! mpegtsmux name=muxer \
        openalsrc ! audioconvert ! avenc_ac3 ! queue max-size-time=10000000000 ! muxer. \
        muxer. ! rtpmp2tpay ! udpsink host=%s port=7002", ip_address);
    system(command);
    return NULL;
}

void* receiver_thread(void* arg) {
    system("gst-launch-1.0 udpsrc port=7001 caps=\"application/x-rtp\" ! \
        rtpmp2tdepay ! decodebin name=decoder ! queue ! \
        audioconvert ! audioresample ! autoaudiosink \
        decoder. ! queue ! videoconvert ! autovideosink");
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IP_address>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pthread_t sender_tid, receiver_tid;

    if (pthread_create(&sender_tid, NULL, sender_thread, argv[1]) != 0) {
        perror("Failed to create sender thread");
        return EXIT_FAILURE;
    }

    if (pthread_create(&receiver_tid, NULL, receiver_thread, NULL) != 0) {
        perror("Failed to create receiver thread");
        return EXIT_FAILURE;
    }

    printf("Terminate using key\n");
    getchar();

    pthread_cancel(sender_tid);
    pthread_cancel(receiver_tid);

    pthread_join(sender_tid, NULL);
    pthread_join(receiver_tid, NULL);

    return EXIT_SUCCESS;
}
