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

void test_queue__update_and_get_average(void) {
    int num_in_queue = 0;
    
    queue__init(&testQueue_new);
    for (int i = 0; i < 3; i++)
    {
        num_in_queue = num_in_queue + 1;
        queue__update_and_get_average(&testQueue_new, num_in_queue);
    }

    TEST_ASSERT_EQUAL(3, queue__update_and_get_average(&testQueue_new, 5));
    TEST_ASSERT_EQUAL(6, queue__update_and_get_average(&testQueue_new, 10));
    TEST_ASSERT_EQUAL(10, queue__update_and_get_average(&testQueue_new, 15));
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
    TEST_ASSERT_EQUAL(10, queue__update_and_get_median(&testQueue_new, 50));
    TEST_ASSERT_EQUAL(10, queue__update_and_get_median(&testQueue_new, 3));
}