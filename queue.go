package structures

import "fmt"

type QNode struct {
    Value string
    Next  *QNode
}

type Queue struct {
    front *QNode
    rear  *QNode
    size  int
}

func NewQueue() *Queue {
    return &Queue{front: nil, rear: nil, size: 0}
}

func (q *Queue) Push(value string) {
    newNode := &QNode{Value: value}
    if q.rear == nil {
        q.front = newNode
        q.rear = newNode
    } else {
        q.rear.Next = newNode
        q.rear = newNode
    }
    q.size++
}

func (q *Queue) Pop() (string, error) {
    if q.front == nil {
        return "", fmt.Errorf("queue is empty")
    }
    value := q.front.Value
    q.front = q.front.Next
    if q.front == nil {
        q.rear = nil
    }
    q.size--
    return value, nil
}

func (q *Queue) Front() (string, error) {
    if q.front == nil {
        return "", fmt.Errorf("queue is empty")
    }
    return q.front.Value, nil
}

func (q *Queue) Rear() (string, error) {
    if q.rear == nil {
        return "", fmt.Errorf("queue is empty")
    }
    return q.rear.Value, nil
}

func (q *Queue) Empty() bool {
    return q.front == nil
}

func (q *Queue) Size() int {
    return q.size
}

func (q *Queue) Print() {
    current := q.front
    fmt.Print("Очередь: ")
    for current != nil {
        fmt.Print(current.Value)
        if current.Next != nil {
            fmt.Print(" -> ")
        }
        current = current.Next
    }
    fmt.Println(" -> NULL")
}

func (q *Queue) Clear() {
    q.front = nil
    q.rear = nil
    q.size = 0
}

func (q *Queue) Serialize() []string {
    result := make([]string, 0, q.size)
    current := q.front
    for current != nil {
        result = append(result, current.Value)
        current = current.Next
    }
    return result
}

func (q *Queue) Deserialize(data []string) {
    q.Clear()
    for _, item := range data {
        q.Push(item)
    }
}