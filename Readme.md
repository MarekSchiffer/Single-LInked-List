## Description
A Single Linked List (SLL) should be First-In-First-Out (FIFO) as it is a list after all. <br>
The SLL is separated into the head, which lives on the stack and the nodes,
which are randomly distributed in the heap. The nodes are basically 16 Bytes,
as they are reduced to the void\* to the element they're holding and the next
pointer. <br>

As the head is clearly separated from the nodes, it can carry some additional information,
such as the size, the free function and a pointer to the tail of the list. <br>

The tail pointer is essential for a Single Linked List, as it makes the list a
FIFO data structure. The tail pointer makes the insertion at the rear O(1),
the same as at the front.

Items should be removed from the front and inserted in the back, that's the natural
order and the functions are simply called `ListInsert` and `ListRemove`.

As this is a generic linked list, the nodes don't carry the data directly but
rather the void\* to the data. The data lives again in another part of the heap,
or the stack, than the nodes itself.  <br>

When initializing the list, a free function should be provided. Given the fact that
every data saved in the list resides somewhere else in the heap, freeing is essential. <br>

However, when relying on the free function, it's important to point out, that the list
can not hold the identical item twice! That means if 10 'a' shall be inserted in the list,
10 separate 'a' have to be created in 10 different parts of the heap. <br>
If the list were to contain multiple nodes, which point to the same position in memory,
the free function, would try to free the same memory twice, which will lead free to
abort. <br>

We could modify freeing by checking if there are identical void\* in the list and removing them
before calling free. This is obviously an expensive operation and we therefore chose not to
do that. It also limits functions such as `ListRemoveNth`, which also has to free before removing 
the node. <br>

Instead of a free function the value NULL can be passed. In that case multiple pointers to the
same part of memory are possible. The client is responsible for freeing the memory in that case. <br>

Every time an item of the list is regained control of and it's living on the heap, it's the clients
responsibility to free the memory. <br>

The provided functions include:
| Function            | Time | Description                                                |
|---------------------|------|------------------------------------------------------------|
| `ListInit`          | O(1) | Initializes a new empty list.                              |
| `ListDispose`       | O(n) | Disposes of the list, freeing the associated memory.       |
| `ListInsert`        | O(1) | Inserts an item in the list.                               |
| `ListRemove`        | O(1) | Removes the first item from the list.                      |
| `ListRemove_Back`   | O(n) | Removes the last item from the list.                       |
| `ListInsert_Front`  | O(1) | Inserts an item at the front of the list.                  |
| `ListLength`        | O(1) | Returns the number of items in the list.                   |
| `ListInsertNth`     | O(N) | Inserts an item at a specified position in the list.       |
| `ListRemoveNth`     | O(N) | Removes the item at a specified position in the list.      |
| `ListReturnNth`     | O(N) | Returns the item at a specified position in the list.      |
| `ListFind`          | O(n) | Searches for an item in the list and returns its position. |
| `ListSort`          | O(n²)| Sorts the list. (Insertion Sort)                           |
| `ListMap`           | O(n) | Applies a function to each item in the list.               |

## How to use:
```
list chrList = ListInit(freeChr);

for(ch = 'A'; ch <= 'Z'; ch++) {
    char* insert = malloc(sizeof(char));
    *insert = ch;
    ListInsert(&chrList,insert);
}
```
Creates the list:
```
ABCDEFGHIJKLMNOPQRSTUVWXYZ
```


```
   void* removeItem = malloc(sizeof(char));
   ReturnNth(&chrList,(char*)removeItem,11)
```
The list now looks like:
```
ABCDEFGHIJKLNOPQRSTUVWXYZ
```
Finally, we need to free removeItem and the list.
```
Dispose(&chrList);
free(removeItem;
```
### License

**© 2011 Marek Schiffer**

### Acknowledgements
