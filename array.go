package structures

import "fmt"

type DynamicArray struct {
    data []string
    size int
}

func NewDynamicArray(initialCapacity int) *DynamicArray {
    if initialCapacity <= 0 {
        initialCapacity = 10
    }
    return &DynamicArray{
        data: make([]string, initialCapacity),
        size: 0,
    }
}

func (da *DynamicArray) PushBack(value string) {
    if da.size >= len(da.data) {
        da.ensureCapacity(da.size + 1)
    }
    da.data[da.size] = value
    da.size++
}

func (da *DynamicArray) Insert(index int, value string) error {
    if index < 0 || index > da.size {
        return fmt.Errorf("index out of range")
    }
    
    if da.size >= len(da.data) {
        da.ensureCapacity(da.size + 1)
    }
    
    copy(da.data[index+1:], da.data[index:da.size])
    da.data[index] = value
    da.size++
    return nil
}

func (da *DynamicArray) Remove(index int) (string, error) {
    if index < 0 || index >= da.size {
        return "", fmt.Errorf("index out of range")
    }
    
    value := da.data[index]
    copy(da.data[index:], da.data[index+1:da.size])
    da.size--
    da.data[da.size] = ""
    return value, nil
}

func (da *DynamicArray) Set(index int, value string) error {
    if index < 0 || index >= da.size {
        return fmt.Errorf("index out of range")
    }
    da.data[index] = value
    return nil
}

func (da *DynamicArray) Get(index int) (string, error) {
    if index < 0 || index >= da.size {
        return "", fmt.Errorf("index out of range")
    }
    return da.data[index], nil
}

func (da *DynamicArray) Find(value string) int {
    for i := 0; i < da.size; i++ {
        if da.data[i] == value {
            return i
        }
    }
    return -1
}

func (da *DynamicArray) Size() int {
    return da.size
}

func (da *DynamicArray) Capacity() int {
    return len(da.data)
}

func (da *DynamicArray) Clear() {
    for i := 0; i < da.size; i++ {
        da.data[i] = ""
    }
    da.size = 0
}

func (da *DynamicArray) Print() {
    fmt.Printf("Массив [%d/%d]: ", da.size, len(da.data))
    for i := 0; i < da.size; i++ {
        fmt.Printf("\"%s\"", da.data[i])
        if i < da.size-1 {
            fmt.Print(", ")
        }
    }
    fmt.Println()
}

func (da *DynamicArray) Serialize() []string {
    result := make([]string, da.size)
    copy(result, da.data[:da.size])
    return result
}

func (da *DynamicArray) Deserialize(data []string) {
    da.Clear()
    da.ensureCapacity(len(data))
    for _, item := range data {
        da.PushBack(item)
    }
}

func (da *DynamicArray) ensureCapacity(requiredSize int) {
    if requiredSize > len(da.data) {
        newCapacity := len(da.data) * 2
        if newCapacity < requiredSize {
            newCapacity = requiredSize + 10
        }
        newData := make([]string, newCapacity)
        copy(newData, da.data)
        da.data = newData
    }
}