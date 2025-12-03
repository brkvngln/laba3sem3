package structures

import "fmt"

type StackNode struct {
    Value string
    Next  *StackNode
}

type Stack struct {
    top  *StackNode
    size int
}

func NewStack() *Stack {
    return &Stack{top: nil, size: 0}
}

func (s *Stack) Push(value string) {
    newNode := &StackNode{Value: value, Next: s.top}
    s.top = newNode
    s.size++
}

func (s *Stack) Pop() (string, error) {
    if s.top == nil {
        return "", fmt.Errorf("stack is empty")
    }
    value := s.top.Value
    s.top = s.top.Next
    s.size--
    return value, nil
}

func (s *Stack) Top() (string, error) {
    if s.top == nil {
        return "", fmt.Errorf("stack is empty")
    }
    return s.top.Value, nil
}

func (s *Stack) Empty() bool {
    return s.top == nil
}

func (s *Stack) Size() int {
    return s.size
}

func (s *Stack) Print() {
    current := s.top
    fmt.Print("Стек: ")
    for current != nil {
        fmt.Print(current.Value)
        if current.Next != nil {
            fmt.Print(" -> ")
        }
        current = current.Next
    }
    fmt.Println(" -> NULL")
}

func (s *Stack) Clear() {
    s.top = nil
    s.size = 0
}

func (s *Stack) Serialize() []string {
    result := make([]string, 0, s.size)
    current := s.top
    for current != nil {
        result = append(result, current.Value)
        current = current.Next
    }
    return result
}

func (s *Stack) Deserialize(data []string) {
    s.Clear()
    for i := len(data) - 1; i >= 0; i-- {
        s.Push(data[i])
    }
}