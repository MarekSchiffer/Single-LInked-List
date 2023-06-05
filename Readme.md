## Description
A Single Linked List (SLL) should be FIFO as it is a list after all.
The SLL is separated into the head, which lives on the stack and the nodes,
which are randomly distributed in he heap. The nodes are basically 16 Bytes,
as they are reduced to the void\* to the element they're holding and the next pointer.

As the head is clearly seperated from the nodes, it can carry some additional information, 
such as the size, the free function and a pointer to the tail of the list.

The tail pointer is essential for a Single Linked List, as it makes the list a
First-In-First-Out data structure. It's a list after all. The tail pointer makes
the insertion at the rear O(1), the same as at the front. 

Items should be removed from the front and inserted in the back, that's the natural
order. 

As this is a C generic linked list, the nodes don't carry the data directly but
rather the void\* to the data. The data lives again in another part of the heap
or the stack than the node itself. 

When initializing the list, a free function should be provided. Given the fact that
every data saved in the list resides somewhere else in the heap, freeing is essential.

However, when relying on the free function, it's important to point out, that the list 
can not hold the identical item twice! That means if 10 'a' shall be inserted in the list, 
10 separate 'a' have to be created in 10 different parts of the heap. 
If the list were to contain multiple nodes, which point to the same position in memory,
the free function, would try to free the same memory twice, which will lead free to
Abort.

We could modify freeing by checking if there are identical void\* in the list and removing them
before calling free. This is obviously an expensive operation and we therefore chose not to 
do that. It also limits functions such as ListRemoveNTh, which also has to free the before
removing the node. In 

Instead of a free function the value NULL can be passed. In that case multiple pointers to the
same part of memory are possible. The client is responsible for freeing the memory in that case.

The provided functions include:

- `ListInit`: Initializes a new empty list.
- `ListDispose`: Disposes of the list, freeing the associated memory.
- `ListInsert`: Inserts an item at the front of the list.
- `ListRemove`: Removes the first occurrence of an item from the list.
- `ListRemove_Back`: Removes the last item from the list.
- `ListInsert_Front`: Inserts an item at the front of the list.
- `ListLength`: Returns the number of items in the list.
- `ListInsertNth`: Inserts an item at a specified position in the list.
- `ListRemoveNth`: Removes the item at a specified position in the list.
- `ListReturnNth`: Returns the item at a specified position in the list.
- `ListFind`: Searches for an item in the list and returns its position.
- `ListSort`: Sorts the list.
- `ListMap`: Applies a function to each item in the list.

Please note that this is a C implementation, and it is up to the client to manage memory and ensure proper usage.

