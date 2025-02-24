#include<stdio.h>

int main() {
    int packet_size, rate_of_outgoing, buffer_capacity, total_inputs, current_buffer = 0;  

    printf("Enter buffer capacity :");
    scanf("%d",&buffer_capacity);
    printf("Enter outgoing packet rate :");
    scanf("%d",&rate_of_outgoing);
    printf ("Enter the number of packet inputs :");
    scanf("%d",&total_inputs);
    while (total_inputs != 0) {
        printf("Enter the packet size to be processed : ");
        scanf("%d", &packet_size);
        printf("Processing packet size %d\n", packet_size);

        if (packet_size <= (buffer_capacity - current_buffer)) {
            current_buffer += packet_size;
            printf("Buffer state:  %d out of %d\n", current_buffer, buffer_capacity);
        } else {
            printf("Dropped %d packet(s)\n", packet_size - (buffer_capacity - current_buffer));
            current_buffer = buffer_capacity;
            printf("Buffer state:  %d out of %d\n", current_buffer, buffer_capacity);
        }

        if(current_buffer >= rate_of_outgoing) {
            current_buffer -= rate_of_outgoing;
        }

        if(current_buffer < 0) {
            current_buffer = -current_buffer;
        }

        printf("After outgoing process, %d packets remain in buffer, capacity: %d\n", current_buffer, buffer_capacity);

        total_inputs--;
    }

    return 0;
}

