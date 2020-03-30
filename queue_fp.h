#ifndef QUEUE_FP_H
#define QUEUE_FP_H
#include"types.h"
#include <stdio.h>

/***@briefStructure to implement a queue. To be defined in queue_fp.c***/
typedef struct _Queue Queue;

/***@briefTypedef for a function pointer to free a queue element**/
typedef void(*destroy_element_function_type)(void*);

/***@briefTypedef for a function pointer to copy a queue element**/
typedef void*(*copy_element_function_type)(const void*);

/***@briefTypedef for a function pointer to print a queue element**/
typedef int(*print_element_function_type)(FILE*,const void*);


/***@briefThis function initializes an empty queue.*
*@paramf1A pointer to a funcion to free a element of the queue.
*@paramf2A pointer to a funcion to copy a element of the queue.
*@paramf3A pointer to a funcion to print a element of the queue.
*@returnThis function returns a pointer to the queue or a null
* pointer if insufficient memory is available to create the queue.*  
*/
Queue* queue_init(destroy_element_function_type f1,copy_element_function_type f2, print_element_function_type f3);


/***@briefThis function frees all the memory used by the queue.
 * *@paramsA pointer to the queue*  
 * */
void queue_free(Queue *q);
/***@briefReturns whether the queue is empty
 * *@paramsA pointer to the queue.*
 * @returnTRUE or FALSE
 * */
Bool queue_isEmpty(const Queue *q);


/***@briefThis function is used to insert a element at the queue.
 * ** A copy of the element is added to the queue container and the
 * * size of the queue is increased by 1. Time complexity: O(1).
 * * This function allocates memory for a copy of the element.
 * *@paramsA pointer to the queue.
 * *@parameleA pointer to the element to be inserted*
 * @returnThis function returns OK on success or ERROR if
 * * insufficient memory is available to allocate the element.
 * *  */
Status queue_insert(Queue *q,const void* pElem);


/***@briefThis function is used to extract a element from the top of the queue.*
 * * The size of the queue is decreased by 1. Time complexity: O(1).
 * *@paramsA pointer to the queue.
 * *@returnThis function returns a pointer to the extracted element
 * * on success or null when the queue is empty.* 
 * */
void* queue_extract(Queue *q);


/***@briefThis function returns the size of the queue.*
 * * Time complexity: O(1).
 * *@paramsA pointer to the queue.
 * *@returnthe queue size
 * */
int queue_size (const Queue *q);


 /***@brief This function writes the elements of the queue to the stream.
  * *@paramf pA pointer to the stream
  * *@params A pointer to the element to the queue
  * *@return Upon successful return, these function returns the
  * * number of characters writted. The function returns a negative
  * * value if there was a problem writing to the file.*  
  * */
int queue_print(FILE*pf,const Queue *q);
 
#endif