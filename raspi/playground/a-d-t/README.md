[**SOURCE_1**](https://www.programiz.com/dsa/queue)
[**SOURCE_2**](https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/)
[**SOURCE_3**](https://techvedas-learn.com/category/algorithm/)
[**SOURCE_4**](https://dev.to/iuliagroza/complete-introduction-to-the-30-most-essential-data-structures-algorithms-43kd)

In this doc some ADT described:

1. Ring buffer (circular buffer)
2. Stack (LIFO)
3. Queue (FIFO)
4. Linked list
5. Tree

**General NOTE (related to all ADT):**
There are many ways to implement ADT, it can be array-based, pointer-based or based on other ADT.

### CIRCULAR (RING) BUFFER

### Description

**Circular buffer** (further - **CB**) is a FIFO data structure that treats memory to be circular; that is, the read/write indices loop back to 0 after it reaches the buffer length. 
This is achieved by two pointers to the array, the **Head** pointer and the **Tail** pointer. 
As data is added (write) to the buffer, the **Head** pointer is incremented and likewise, when the data is being removed (read) the **Tail** pointer is incremented. 

#### Rules:

1. There should be 2 indexes. For example: **HEAD @ TAIL**;
2. Write (Enqueue) should start at **HEAD** index and then advance it;
3. Read (Dequeue) should start at **TAIL** index and then advance it;
4. If the end of the buffer reached, indexes will wrap around. Modulo operation shuold be applied each time index increments;

#### Conditions:

*Full*:     **HEAD + 1** == **TAIL**
*Empty*:    **HEAD == TAIL**
*Initail*:  **HEAD == TAIL == 0**

### Main Operations:

* put **Item** to the buffer (Enqueue operation);
* retrieve **Item** from the buffer (Dequeue operation);

#### Enqueue Steps:

* verify whether the buffer is *Full*, if *Full* return *false*, otherwise continue;
* add new **Item** to the buffer where **HEAD** is pointing;
* advance **HEAD** ( head = (head + 1) % buffer_size )

#### Dequeue Steps:

* verify whether the buffer is *Empty*, if *Empty* return *false*, otherwise continue;
* retrieve **Item** from the buffer where **TAIL** is pointing;
* advance **TAIL** ( tail = (tail + 1) % buffer_size )

**NOTE:** Aforementioned conditions called **"Waste"** and it is **Thread-safe**, because data "Consumer" and "Producer" access corresponding indexes.
There is another way to define *Full* and *Empty* condition using bool **Flag**. This approach involse different logic and extra logic should be consider
to provide **Thread-safe** usage.

**NOTE:** What should be done when new data arrived, but the buffer is *Full*?
There are two ways: 
* discard new data (Not add new data, use bool to return);
* discard the oldest data (add new data to the buffer and advance **TAIL**); 

### STACK (LIFO)

#### Description

**Stack** is an abstract data type with a bounded(predefined) capacity. It is a simple data structure that allows adding and removing elements in a particular order.
Every time an element is added, it goes on the top of the stack and the only element that can be removed is the element that is at the top of the stack, just like a pile of objects.

#### Rules:

1. There is one index, called **Top**, pointing to the top of the **Stack**;
2. Write (Push) should start at **Top** index, and advance it;
3. Read (Pop) should stast at **Top** index, and decrease it;
4. If the end of the buffer reached, means the **Stack** is *Full* and nothing should be done.

#### Conditions:

*Full*:     **TOP** == **Size - 1**
*Empty*:    **TOP == -1**
*Initail*:  **TOP == -1**

### Main Operations:

* push **Item** to the buffer (Enqueue operation);
* pop **Item** from the buffer (Dequeue operation);

#### Push Steps:

* verify whether the buffer is *Full*, if *Full* return *false*, otherwise continue;
* advance **TOP**;
* add new **Item** to the buffer, where **TOP** is pointing;

#### Pop Steps:

* verify whether the buffer is *Empty*, if *Empty* return *false*, otherwise continue;
* retrieve **Item** from the buffer, where **TOP** is pointing;
* decrement **TOP**;

### QUEUE (FIFO)

#### Description

A **Queue** is a linear data structure that stores a collection of elements. The queue operates on first in first out (FIFO) algorithm. 

#### Rules:

1. There are 2 indexes (pointers): **FRONT & REAR**;
2. Write (Enqueue) should start at **REAR** index and then advance it;
3. Read (Dequeue) should start at **FRONT** index and then advance it;
4. If the end of the buffer reached, indexes will wrap around. Modulo operation shuold be applied each time index increments;

#### Conditions:

*Full*:     **COUNTER** == **CAPACITY**
*Empty*:    **COUNTER == 0**
*Initail*:  **FRONT == 0; REAR == SIZE - 1**

### Main Operations:

* enqueue **Item** to the buffer (Enqueue operation);
* dequeue **Item** from the buffer (Dequeue operation);

#### Enqueue Steps:

* verify whether the buffer is *Full*, if *Full* return *false*, otherwise continue;
* advance **REAR** ( (Rear + 1) % Capacity);
* add new **Item** to the buffer where **REAR** is pointing;
* increment **Counter**;

#### Dequeue Steps:

* verify whether the buffer is *Empty*, if *Empty* return *false*, otherwise continue;
* retrieve **Item** from the buffer, where **FRONT** is pointing;
* advance **FRONT** ( (Front + 1) % Capacity);
* decrement **Counter**;

### LINKED LIST

#### Description

A **Linked List** is a linear data structure. Every linked list has two parts, the data section and the address section that holds the address of the next element in the list, which is called a node.

#### Rules:

1. Each **Node** contains 2 fields:
    * **".data"** field to store whatever element type the list holds
    * **".next"** field which is a pointer used to link one node to the next node;
2. Each **Node** contains a single **.next** pointer to the next **Node**;
3. The **.next** pointer of the last **Node** is **NULL**;
4. All of the **Nodes** are allocated in the **heap**.

#### Conditions:

*Full*:      - 
*Empty*:     - 
*Initail*:   - 

### Main Operations:

* Traversal - access each element of the linked list
* Insertion - adds a new element to the linked list
* Deletion - removes the existing elements
* Peek - "look" at the Item without removing it
* Search - find a node in the linked list
* Sort - sort the nodes of the linked list

#### Enqueue Steps:

**NOTE:** **Head** and **User Data** should be passed as a parameter.
This is done to link newNode to the previous (in this case: **Head**)

**case 1: (Add Item at the end)**

* allocate **newNode** in the **heap** and set **.data** to whatever needs to be stored (malloc);
* link newNode **.next** to the current **Node** of the list (newNode->next = head);
* link **Head** to **newNode** (head = newNode), so head is the first **Item** in the **list**;

**case 2: (Add Item at the beginning)**

* allocate **newNode** in the **heap** and set **.data** to whatever needs to be stored (malloc);
* set **newNode** **.next = NULL** (in this case new node will be the last Item in the list);
* check whether **Head** is the fist Item in the list (head == NULL), if so head = newNode; if not move further
* iterete (traverse) over the list to reach **Node** with **.next** == NULL;
* link current **Node**.next to newNode (current->next = newNode);

**case 3: (Add Item at the middle)**

**NOTE:** In this case a **key** field is need to identify the rigth Node

**NOTE:**
**!!!** In order to modify **"right"** head, a *pointer-to-pointer* should be used.

#### Dequeue Steps (Delete Item):

**case 1: (Delete using additional pointer)**

* inside function two **Node** type pointers should be declared (**current & previous**). 
Current tracks current **Node**, previous tracks previous **Node**.
* iterate over List using current pointer and save current to previous (previous = current)
* once **key** is found, check whether it is first Item, if so advance **Head** (head = current->next), if not
* advance previous->next to current->next

**case 2: (Delete using pointer-to-pointer)**

* inside function pointer-to-pointer of Node type should be declared and assign to head;
* iterate over List using pointer-to-pointer (advance pointer-to-pointer);
* once **key** is found, dereference pointer-to-pointer and advance to next;

### TREE

#### Description

A **tree** is a nonlinear hierarchical data structure that consists of nodes connected by edges.
Tree terminology:

* **Node**
A node is an entity that contains a key or value and pointers to its child nodes.
The last nodes of each path are called **leaf nodes or external nodes** that do not contain a link/pointer to child nodes.
The node having at least a child node is called an internal node.

* **Edge**
It is the link between any two nodes.

* **Root**
It is the topmost node of a tree.

#### Rules:

#### Conditions:




