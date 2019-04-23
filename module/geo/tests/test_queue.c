#include "unity.h"
#include "c_queue.h"

queue_S q1;
queue_S *queue=&q1;
uint8_t pop_value;

void test_queue__init(void){
	queue__init(queue);
	TEST_ASSERT_EQUAL_UINT8(0, queue->front);
	TEST_ASSERT_EQUAL_UINT8(0, queue->rear);
}


void test_queue__push(void){

	for(int i=1;i<=100;i++){
		TEST_ASSERT_TRUE(queue__push(queue,i));
	}
		TEST_ASSERT_EQUAL_UINT8(1, queue->front);
		TEST_ASSERT_EQUAL_UINT8(100, queue->rear);
		TEST_ASSERT_EQUAL_UINT8(100, queue__get_count(queue));
	
	TEST_ASSERT_FALSE(queue__push(queue,101));
}

void test_queue__pop(void){
	for(int i=1;i<=150;i++){
		//TEST_ASSERT_EQUAL_UINT8(90, queue__get_count(queue));
		TEST_ASSERT_TRUE(queue__pop(queue,&pop_value)); 
	}
		TEST_ASSERT_EQUAL_UINT8(100,pop_value);
		TEST_ASSERT_EQUAL_UINT8(0,queue->front);
		TEST_ASSERT_EQUAL_UINT8(100,queue->rear);
		TEST_ASSERT_EQUAL_UINT8(0, queue__get_count(queue));

	
	//TEST_ASSERT_TRUE(queue__pop(queue,&pop_value));
	TEST_ASSERT_EQUAL_UINT8(0, queue__get_count(queue));
	for(int i=1;i<=10;i++)
	{
		TEST_ASSERT_TRUE(queue__push(queue,i));
	
    }
    TEST_ASSERT_TRUE(queue__get_count(queue));
    TEST_ASSERT_EQUAL_UINT8(10, queue__get_count(queue));
    
	for(int i=1;i<=600;i++){
		//TEST_ASSERT_EQUAL_UINT8(90, queue__get_count(queue));
		TEST_ASSERT_TRUE(queue__pop(queue,&pop_value)); 
	}
	
	
	
}



//void test_my_tests(void)
//{
	