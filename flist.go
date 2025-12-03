package structures

import "fmt"

type SNode struct {
    Value string
    Next  *SNode
}

type SinglyLinkedList struct {
    head *SNode
    size int
}

func NewSinglyLinkedList() *SinglyLinkedList {
    return &SinglyLinkedList{head: nil, size: 0}
}

func (sll *SinglyLinkedList) PushFront(value string) {
    newNode := &SNode{Value: value, Next: sll.head}
    sll.head = newNode
    sll.size++
}

func (sll *SinglyLinkedList) PushBack(value string) {
    newNode := &SNode{Value: value}
    if sll.head == nil {
        sll.head = newNode
    } else {
        current := sll.head
        for current.Next != nil {
            current = current.Next
        }
        current.Next = newNode
    }
    sll.size++
}

func (sll *SinglyLinkedList) Find(value string) *SNode {
    current := sll.head
    for current != nil {
        if current.Value == value {
            return current
        }
        current = current.Next
    }
    return nil
}

func (sll *SinglyLinkedList) AddAfter(node *SNode, value string) error {
    if node == nil {
        return fmt.Errorf("node cannot be nil")
    }
    newNode := &SNode{Value: value, Next: node.Next}
    node.Next = newNode
    sll.size++
    return nil
}

func (sll *SinglyLinkedList) DeleteAfter(node *SNode) error {
    if node == nil || node.Next == nil {
        return fmt.Errorf("no node to delete after")
    }
    node.Next = node.Next.Next
    sll.size--
    return nil
}

func (sll *SinglyLinkedList) AddBefore(node *SNode, value string) error {
    if node == nil {
        return fmt.Errorf("node cannot be nil")
    }
    
    if sll.head == node {
        sll.PushFront(value)
        return nil
    }
    
    current := sll.head
    for current != nil && current.Next != node {
        current = current.Next
    }
    
    if current == nil {
        return fmt.Errorf("node not found in list")
    }
    
    newNode := &SNode{Value: value, Next: node}
    current.Next = newNode
    sll.size++
    return nil
}

func (sll *SinglyLinkedList) DeleteBefore(node *SNode) error {
    if node == nil || sll.head == nil || sll.head == node {
        return fmt.Errorf("no node to delete before")
    }
    
    if sll.head.Next == node {
        sll.head = sll.head.Next
        sll.size--
        return nil
    }
    
    current := sll.head
    for current != nil && current.Next != nil && current.Next.Next != node {
        current = current.Next
    }
    
    if current == nil || current.Next == nil {
        return fmt.Errorf("node not found")
    }
    
    current.Next = current.Next.Next
    sll.size--
    return nil
}

func (sll *SinglyLinkedList) PopFront() (string, error) {
    if sll.head == nil {
        return "", fmt.Errorf("list is empty")
    }
    value := sll.head.Value
    sll.head = sll.head.Next
    sll.size--
    return value, nil
}

func (sll *SinglyLinkedList) DeleteByKey(value string) bool {
    if sll.head == nil {
        return false
    }
    
    if sll.head.Value == value {
        sll.head = sll.head.Next
        sll.size--
        return true
    }
    
    current := sll.head
    for current.Next != nil {
        if current.Next.Value == value {
            current.Next = current.Next.Next
            sll.size--
            return true
        }
        current = current.Next
    }
    return false
}

func (sll *SinglyLinkedList) GetAt(index int) (string, error) {
    if index < 0 || index >= sll.size {
        return "", fmt.Errorf("index out of range")
    }
    
    current := sll.head
    for i := 0; i < index; i++ {
        current = current.Next
    }
    return current.Value, nil
}

func (sll *SinglyLinkedList) Size() int {
    return sll.size
}

func (sll *SinglyLinkedList) Print() {
    current := sll.head
    fmt.Print("Односвязный список: ")
    for current != nil {
        fmt.Print(current.Value)
        if current.Next != nil {
            fmt.Print(" -> ")
        }
        current = current.Next
    }
    fmt.Println(" -> NULL")
}

func (sll *SinglyLinkedList) Clear() {
    sll.head = nil
    sll.size = 0
}

func (sll *SinglyLinkedList) Serialize() []string {
    result := make([]string, 0, sll.size)
    current := sll.head
    for current != nil {
        result = append(result, current.Value)
        current = current.Next
    }
    return result
}

func (sll *SinglyLinkedList) Deserialize(data []string) {
    sll.Clear()
    for _, item := range data {
        sll.PushBack(item)
    }
}

func (sll *SinglyLinkedList) GetHead() *SNode {
    return sll.head
}