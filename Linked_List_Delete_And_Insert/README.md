# Singly Linked List — C++ (Windows)

## Overview

This project implements a **Singly Linked List in C++** and demonstrates basic insertion, deletion, and display operations.

The program was developed and tested in a **Windows environment** using a C++ compiler and Git for version control.

### Operations Implemented

- Insert node at the beginning
- Insert node at the end
- Delete node from the beginning
- Delete node from the end
- Display the linked list

---

## Improvements Made

The original implementation had issues with **edge-case handling** and **memory management**. The updated version fixes these problems.

### 1. Improved `deleteNodeAtEnd()`

The return type was changed from:

```cpp
void deleteNodeAtEnd(ListNode* head)
```

to:

```cpp
ListNode* deleteNodeAtEnd(ListNode* head)
```

The function now returns the updated `head`.

This is important when the linked list contains only one node. After deleting that node, `head` must become `NULL`.

The function is now called using:

```cpp
head = deleteNodeAtEnd(head);
```

---

### 2. Added Empty List Handling

The original code could crash if `deleteNodeAtEnd()` was called on an empty list.

The updated code checks:

```cpp
if(itr == NULL){
    return NULL;
}
```

This prevents invalid pointer access.

---

### 3. Added Single-Node Handling

The updated `deleteNodeAtEnd()` separately handles a list containing only one node:

```cpp
if(itr->next == NULL){
    delete itr;
    head = NULL;
    return head;
}
```

This correctly deletes the node and resets the head.

---

### 4. Replaced `free()` with `delete`

The original code used:

```cpp
free(temp);
```

However, nodes are created using:

```cpp
new ListNode;
```

In C++, memory allocated using `new` must be released using `delete`.

Therefore:

```cpp
new       → delete
malloc()  → free()
```

The updated implementation uses:

```cpp
delete temp;
```

---

### 5. Improved `deleteNodeAtStart()`

The deletion-at-start function now handles all three possible cases.

#### Empty List

```cpp
if(head == NULL){
    return head;
}
```

#### Single Node

```cpp
if(head->next == NULL){
    delete head;
    head = NULL;
    return head;
}
```

#### Multiple Nodes

```cpp
head = head->next;
delete temp;
```

This prevents invalid memory access and correctly updates the head pointer.

---

## Edge Cases Handled

| Case | Original | Updated |
|---|---|---|
| Delete from empty list | ❌ | ✅ |
| Delete only node from list | ❌ | ✅ |
| Delete first node from empty list | ❌ | ✅ |
| Delete first node from single-node list | ❌ | ✅ |
| Correct memory deallocation | ❌ `free()` | ✅ `delete` |
| Updated head after deletion | ❌ | ✅ |

---

## Example

### Input

```text
5
10 20 30 40 50
```

### Initial List

```text
10->20->30->40->50->nullptr
```

### After Deleting From End

```text
10->20->30->40->nullptr
```

### After Deleting From Start

```text
20->30->40->nullptr
```

### After Inserting at Start

If the user enters:

```text
5
```

The final list becomes:

```text
5->20->30->40->nullptr
```

---

## Time Complexity

| Operation | Time Complexity |
|---|---:|
| Insert at Beginning | `O(1)` |
| Insert at End | `O(n)` |
| Delete at Beginning | `O(1)` |
| Delete at End | `O(n)` |
| Display | `O(n)` |

---

## Windows Development Environment

Recommended setup:

- **Operating System:** Windows
- **Language:** C++
- **Compiler:** MinGW / GCC or MSVC
- **Editor:** VS Code / Visual Studio
- **Version Control:** Git

### Compile Using GCC / MinGW

Open **Command Prompt** or **PowerShell** in the project directory:

```bash
g++ linked_list.cpp -o linked_list.exe
```

Run the program:

```bash
.\linked_list.exe
```

---

## Git Line Endings on Windows

Windows commonly uses **CRLF** line endings, while Linux and macOS commonly use **LF**.

Git may therefore display a warning such as:

```text
LF will be replaced by CRLF the next time Git touches it
```

This is a **warning, not an error**.

For a Windows-based repository, Git can be configured to automatically handle line endings:

```bash
git config --global core.autocrlf true
```

Check the current configuration:

```bash
git config --global core.autocrlf
```

If it returns:

```text
true
```

Git will automatically convert line endings appropriately when working on Windows.

---

## Git Commands

To add the updated files:

```bash
git add .
```

Commit the changes:

```bash
git commit -m "Improve linked list deletion and memory handling"
```

Push to GitHub:

```bash
git push
```

---

## Key Learning

The major improvements in this version are:

1. **Proper edge-case handling**
2. **Correct use of `new` and `delete`**
3. **Safe deletion from empty lists**
4. **Safe deletion from single-node lists**
5. **Correctly updating the `head` pointer**
6. **Better memory management**

For linked-list deletion, always consider:

```text
Empty List
     ↓
Single Node
     ↓
Multiple Nodes
```

Handling these cases prevents most common linked-list pointer errors.