#include "unity.h"
#include "queue.h"

queue_S testQueue;
queue_S testQueue_new;

void setUp(void) {
}
void tearDown(void) {
}

void test_queue__init(void){
    
    queue__init(&testQueue);
    TEST_ASSERT_EQUAL(0,testQueue.front);
    TEST_ASSERT_EQUAL(-1,testQueue.rear);
    TEST_ASSERT_EQUAL(0,testQueue.size);
}

void test_queue__push(void)
{
    int num_in_queue = 0;
    for (int i = 0; i < 3; i++)
    {
        num_in_queue = num_in_queue + 1;
        TEST_ASSERT_TRUE(queue__push(&testQueue, num_in_queue));
        TEST_ASSERT_EQUAL(num_in_queue, testQueue.queue_memory[testQueue.rear]);
        TEST_ASSERT_EQUAL(i + 1, queue__get_count(&testQueue));
        TEST_ASSERT_EQUAL(i, testQueue.rear);
        TEST_ASSERT_EQUAL(0, testQueue.front);
    }
    
    /*The queue__push function should return false when the user tries to push when the testQueue is full*/
    TEST_ASSERT_FALSE(queue__push(&testQueue, num_in_queue));
    TEST_ASSERT_EQUAL(3, queue__get_count(&testQueue));
    TEST_ASSERT_EQUAL(2, testQueue.rear);
    TEST_ASSERT_EQUAL(0, testQueue.front);
    
}

void test_queue__pop(void){

    /* Pop out all the elements from the queue
     * Should return true when executing queue__pop
     * size should decrement by 1 in every loop and it should go to 0 at the end of the for loop
     * testQueue.rear should remain in 99 (Since there are no elements pushed in the queue)
     * testQueue.front should increment by 1 in every loop
     */
    int num_from_queue;
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_TRUE(queue__pop(&testQueue, &num_from_queue));
        TEST_ASSERT_EQUAL(i+1, testQueue.front);
        TEST_ASSERT_EQUAL(2, testQueue.rear);
        TEST_ASSERT_EQUAL(3-i-1, queue__get_count(&testQueue));
    }
    /* Return false when trying to execute the queue__pop function when the size is 0
     */
    TEST_ASSERT_FALSE(queue__pop(&testQueue, &num_from_queue));
    TEST_ASSERT_EQUAL(3, testQueue.front);
    TEST_ASSERT_EQUAL(2, testQueue.rear);
    TEST_ASSERT_EQUAL(0, queue__get_count(&testQueue));
}

void test_queue__get_count(void){

    TEST_ASSERT_EQUAL(0, queue__get_count(&testQueue));
}

/* Simulate a circular queue operations
 * Test Step:
 * Step 0: Initialize the queue ()
 * Step 1: Push 100 elements into the queue(Size = 100)
 * Step 2: Pop 50
 *  
 */ 

/*
void test_queue__circular_queue(void){

    queue__init(&testQueue);

    //Push a 100 elements; Size = 100
    uint8_t char_in_queue = 'a';
    for (int i = 0; i < 100; i++)
    {
        TEST_ASSERT_TRUE(queue__push(&testQueue, char_in_queue));
        TEST_ASSERT_EQUAL(char_in_queue, testQueue.queue_memory[testQueue.rear]);
        TEST_ASSERT_EQUAL(i + 1, queue__get_count(&testQueue));
        TEST_ASSERT_EQUAL(i, testQueue.rear);
        TEST_ASSERT_EQUAL(0, testQueue.front);
    }
    Return false when trying to push an element when the queue is full
    TEST_ASSERT_FALSE(queue__push(&testQueue, char_in_queue));

    //Pop 50 elements; Size = 50
    uint8_t char_from_queue = ' ';
    for (int i = 0; i < 50; i++) {
        TEST_ASSERT_TRUE(queue__pop(&testQueue, &char_from_queue));
        TEST_ASSERT_EQUAL(i+1, testQueue.front);
        TEST_ASSERT_EQUAL(99, testQueue.rear);
        TEST_ASSERT_EQUAL(100-i-1, queue__get_count(&testQueue));
    }
    
    Current Queue Information:
     * Size = 50;
     * Queue.front = 51;
     * Queue.rear = 99;
     * If I push '@' into the queue, the element should be stored in testQueue.queue_memory[0] == '@' 
     
    char_in_queue = '@';
    TEST_ASSERT_TRUE(queue__push(&testQueue, char_in_queue));
    TEST_ASSERT_EQUAL('@', testQueue.queue_memory[0]);

    //Push another 30 elements; Size is now 81
    for (int i = 0; i < 30; i++)
    {
        TEST_ASSERT_TRUE(queue__push(&testQueue, char_in_queue));
        TEST_ASSERT_EQUAL(char_in_queue, testQueue.queue_memory[testQueue.rear]);
    }
    
    //Pop 80 elements out from the queue; Size is now 0
    for (int i = 0; i < 81; i++) {
        TEST_ASSERT_TRUE(queue__pop(&testQueue, &char_from_queue));
    }

    Return false when popping an element when the size = 0
    TEST_ASSERT_FALSE(queue__pop(&testQueue, &char_from_queue));
}
*/
void test_queue__update_and_get_average(void) {
    int num_in_queue = 0;
    
    queue__init(&testQueue_new);
    for (int i = 0; i < 3; i++)
    {
        num_in_queue = num_in_queue + 1;
        queue__update_and_get_average(&testQueue_new, num_in_queue);
    }

    TEST_ASSERT_EQUAL(2, queue__update_and_get_average(&testQueue_new, 3));

}


void test_queue__update_and_get_median(void) {
    int num_in_queue = 0;
    
    queue__init(&testQueue_new);
    for (int i = 0; i < 3; i++)
    {
        num_in_queue = num_in_queue + 1;
        queue__update_and_get_median(&testQueue_new, num_in_queue);
    }

    TEST_ASSERT_EQUAL(3, queue__update_and_get_median(&testQueue_new, 10));

}