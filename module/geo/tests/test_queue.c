#include "unity.h"

#include "queue.h"

queue_S q1;
#define QUEUE_MAX 10

//, queue_S *queue=&q1;
//uint8_t pop_value;

void test_queue__init(void){
    queue__init(&q1);
    TEST_ASSERT_EQUAL_UINT8(0, q1.front);
    TEST_ASSERT_EQUAL_UINT8(-1, q1.rear);
    TEST_ASSERT_EQUAL_UINT8(0, q1.size);
}

void test_queue__push(void)
{
    float push_value = 10;
    TEST_ASSERT_TRUE(queue__push(&q1, push_value));
    TEST_ASSERT_EQUAL_UINT8(1, q1.size);
    TEST_ASSERT_EQUAL_UINT8(0, q1.rear);
    TEST_ASSERT_EQUAL_UINT8(0, q1.front);

    for(int i = 1;i<=2;i++)
    {
        TEST_ASSERT_TRUE(queue__push(&q1, push_value));

    }
    TEST_ASSERT_EQUAL_UINT8(3, q1.size);
    TEST_ASSERT_EQUAL_UINT8(2, q1.rear);
    TEST_ASSERT_EQUAL_UINT8(0, q1.front);

    for(int i=1; i<=5; i++)
    {
        TEST_ASSERT_FALSE(queue__push(&q1, i));
    }

}

void test_queue__pop(void)
{
    float pop_value = 10;
    TEST_ASSERT_TRUE(queue__pop(&q1, &pop_value));
    TEST_ASSERT_EQUAL_UINT8(2, q1.size);
    TEST_ASSERT_EQUAL_UINT8(2, q1.rear);
    TEST_ASSERT_EQUAL_UINT8(1, q1.front);

    TEST_ASSERT_TRUE(queue__pop(&q1, &pop_value));
    TEST_ASSERT_EQUAL_UINT8(1, q1.size);
    TEST_ASSERT_EQUAL_UINT8(2, q1.rear);
    TEST_ASSERT_EQUAL_UINT8(2, q1.front);

    TEST_ASSERT_TRUE(queue__pop(&q1, &pop_value));

    for(int i=1;i<=10;i++)
    {
        TEST_ASSERT_FALSE(queue__pop(&q1, &pop_value));
    }
}

void test_queue__update_and_get_average(void)
{
    q1.size = 3;
    q1.sum = 10;
    float pop_value = 5.5;
    queue__update_and_get_average(&q1, pop_value);
    TEST_ASSERT_TRUE(queue__pop(&q1, &pop_value));
    TEST_ASSERT_EQUAL_FLOAT(5.5, q1.sum);
}

