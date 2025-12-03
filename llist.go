package structures

import "fmt"

type DNode struct {
    Value string
    Next  *DNode
    Prev  *DNode
}

type DoublyLinkedList struct {
    head *DNode
    tail *DNode
    size int
}

func NewDoublyLinkedList() *DoublyLinkedList {
    return &DoublyLinkedList{head: nil, tail: nil, size: 0}
}

func (dll *DoublyLinkedList) PushFront(value string) {
    newNode := &DNode{Value: value}
    if dll.head == nil {
        dll.head = newNode
        dll.tail = newNode
    } else {
        newNode.Next = dll.head
        dll.head.Prev = newNode
        dll.head = newNode
    }
    dll.size++
}

func (dll *DoublyLinkedList) PushBack(value string) {
    newNode := &DNode{Value: value}
    if dll.head == nil {
        dll.head = newNode
        dll.tail = newNode
    } else {
        newNode.Prev = dll.tail
        dll.tail.Next = newNode
        dll.tail = newNode
    }
    dll.size++
}

func (dll *DoublyLinkedList) Find(value string) *DNode {
    current := dll.head
    for current != nil {
        if current.Value == value {
            return current
        }
        current = current.Next
    }
    return nil
}

func (dll *DoublyLinkedList) AddAfter(node *DNode, value string) error {
    if node == nil {
        return fmt.Errorf("node cannot be nil")
    }
    
    newNode := &DNode{Value: value}
    newNode.Next = node.Next
    newNode.Prev = node
    
    if node.Next != nil {
        node.Next.Prev = newNode
    }
    node.Next = newNode
    
    if node == dll.tail {
        dll.tail = newNode
    }
    
    dll.size++
    return nil
}

func (dll *DoublyLinkedList) AddBefore(node *DNode, value string) error {
    if node == nil {
        return fmt.Errorf("node cannot be nil")
    }
    
    newNode := &DNode{Value: value}
    newNode.Prev = node.Prev
    newNode.Next = node
    
    if node.Prev != nil {
        node.Prev.Next = newNode
    }
    node.Prev = newNode
    
    if node == dll.head {
        dll.head = newNode
    }
    
    dll.size++
    return nil
}

func (dll *DoublyLinkedList) PopFront() (string, error) {
    if dll.head == nil {
        return "", fmt.Errorf("list is empty")
    }
    
    value := dll.head.Value
    if dll.head == dll.tail {
        dll.head = nil
        dll.tail = nil
    } else {
        dll.head = dll.head.Next
        dll.head.Prev = nil
    }
    
    dll.size--
    return value, nil
}

func (dll *DoublyLinkedList) PopBack() (string, error) {
    if dll.tail == nil {
        return "", fmt.Errorf("list is empty")
    }
    
    value := dll.tail.Value
    if dll.head == dll.tail {
        dll.head = nil
        dll.tail = nil
    } else {
        dll.tail = dll.tail.Prev
        dll.tail.Next = nil
    }
    
    dll.size--
    return value, nil
}

func (dll *DoublyLinkedList) DeleteAfter(node *DNode) error {
    if node == nil || node.Next == nil {
        return fmt.Errorf("no node to delete after")
    }
    
    nodeToDelete := node.Next
    node.Next = nodeToDelete.Next
    
    if nodeToDelete.Next != nil {
        nodeToDelete.Next.Prev = node
    }
    
    if nodeToDelete == dll.tail {
        dll.tail = node
    }
    
    dll.size--
    return nil
}

func (dll *DoublyLinkedList) DeleteBefore(node *DNode) error {
    if node == nil || node.Prev == nil {
        return fmt.Errorf("no node to delete before")
    }
    
    nodeToDelete := node.Prev
    node.Prev = nodeToDelete.Prev
    
    if nodeToDelete.Prev != nil {
        nodeToDelete.Prev.Next = node
    }
    
    if nodeToDelete == dll.head {
        dll.head = node
    }
    
    dll.size--
    return nil
}

func (dll *DoublyLinkedList) DeleteByKey(value string) bool {
    node := dll.Find(value)
    if node == nil {
        return false
    }
    
    if node.Prev != nil {
        node.Prev.Next = node.Next
    } else {
        dll.head = node.Next
    }
    
    if node.Next != nil {
        node.Next.Prev = node.Prev
    } else {
        dll.tail = node.Prev
    }
    
    dll.size--
    return true
}

func (dll *DoublyLinkedList) GetAt(index int) (string, error) {
    if index < 0 || index >= dll.size {
        return "", fmt.Errorf("index out of range")
    }
    
    current := dll.head
    for i := 0; i < index; i++ {
        current = current.Next
    }
    return current.Value, nil
}

func (dll *DoublyLinkedList) Size() int {
    return dll.size
}

func (dll *DoublyLinkedList) Print() {
    current := dll.head
    fmt.Print("Двусвязный список: ")
    for current != nil {
        fmt.Print(current.Value)
        if current.Next != nil {
            fmt.Print(" <-> ")
        }
        current = current.Next
    }
    fmt.Println(" -> NULL")
}

func (dll *DoublyLinkedList) PrintReverse() {
    current := dll.tail
    fmt.Print("Двусвязный список (обратный): ")
    for current != nil {
        fmt.Print(current.Value)
        if current.Prev != nil {
            fmt.Print(" <-> ")
        }
        current = current.Prev
    }
    fmt.Println(" -> NULL")
}

func (dll *DoublyLinkedList) Clear() {
    dll.head = nil
    dll.tail = nil
    dll.size = 0
}

func (dll *DoublyLinkedList) Serialize() []string {
    result := make([]string, 0, dll.size)
    current := dll.head
    for current != nil {
        result = append(result, current.Value)
        current = current.Next
    }
    return result
}

func (dll *DoublyLinkedList) Deserialize(data []string) {
    dll.Clear()
    for _, item := range data {
        dll.PushBack(item)
    }
}

func (dll *DoublyLinkedList) GetHead() *DNode {
    return dll.head
}

func (dll *DoublyLinkedList) GetTail() *DNode {
    return dll.tail
}