package structures

import (
    "fmt"
    "strings"
)

type HashItem struct {
    Key      string
    Value    string
    IsDeleted bool
    IsEmpty   bool
}

type HashTable struct {
    items    []HashItem
    capacity int
    size     int
}

func NewHashTable(capacity int) *HashTable {
    if capacity <= 0 {
        capacity = 10
    }
    items := make([]HashItem, capacity)
    for i := range items {
        items[i] = HashItem{IsEmpty: true}
    }
    return &HashTable{
        items:    items,
        capacity: capacity,
        size:     0,
    }
}

func (ht *HashTable) Insert(key, value string) bool {
    if ht.size >= ht.capacity*7/10 {
        ht.rehash()
    }

    index := ht.hashFunction(key)
    startIndex := index

    for {
        if ht.items[index].IsEmpty || ht.items[index].IsDeleted {
            ht.items[index] = HashItem{
                Key:      key,
                Value:    value,
                IsDeleted: false,
                IsEmpty:   false,
            }
            ht.size++
            return true
        }

        if !ht.items[index].IsDeleted && ht.items[index].Key == key {
            ht.items[index].Value = value
            return true
        }

        index = (index + 1) % ht.capacity
        if index == startIndex {
            return false
        }
    }
}

func (ht *HashTable) Find(key string) (string, bool) {
    index := ht.hashFunction(key)
    startIndex := index

    for {
        if ht.items[index].IsEmpty && !ht.items[index].IsDeleted {
            return "", false
        }

        if !ht.items[index].IsEmpty && !ht.items[index].IsDeleted &&
            ht.items[index].Key == key {
            return ht.items[index].Value, true
        }

        index = (index + 1) % ht.capacity
        if index == startIndex {
            return "", false
        }
    }
}

func (ht *HashTable) Remove(key string) bool {
    index := ht.hashFunction(key)
    startIndex := index

    for {
        if ht.items[index].IsEmpty && !ht.items[index].IsDeleted {
            return false
        }

        if !ht.items[index].IsEmpty && !ht.items[index].IsDeleted &&
            ht.items[index].Key == key {
            ht.items[index].IsDeleted = true
            ht.size--
            return true
        }

        index = (index + 1) % ht.capacity
        if index == startIndex {
            return false
        }
    }
}

func (ht *HashTable) Clear() {
    for i := range ht.items {
        ht.items[i] = HashItem{IsEmpty: true}
    }
    ht.size = 0
}

func (ht *HashTable) Empty() bool {
    return ht.size == 0
}

func (ht *HashTable) Size() int {
    return ht.size
}

func (ht *HashTable) Capacity() int {
    return ht.capacity
}

func (ht *HashTable) Print() {
    fmt.Printf("Хеш-таблица [%d/%d]: ", ht.size, ht.capacity)
    items := ht.getAllItems()
    if len(items) == 0 {
        fmt.Println("пуста")
        return
    }
    
    for i, item := range items {
        fmt.Printf("{%s:%s}", item.Key, item.Value)
        if i < len(items)-1 {
            fmt.Print(", ")
        }
    }
    fmt.Println()
}

func (ht *HashTable) Serialize() []string {
    items := ht.getAllItems()
    result := make([]string, len(items))
    for i, item := range items {
        result[i] = item.Key + ":" + item.Value
    }
    return result
}

func (ht *HashTable) Deserialize(data []string) {
    ht.Clear()
    for _, item := range data {
        parts := strings.Split(item, ":")
        if len(parts) == 2 {
            ht.Insert(parts[0], parts[1])
        }
    }
}

func (ht *HashTable) hashFunction(key string) int {
    hash := 0
    for _, c := range key {
        hash = (hash*31 + int(c)) % ht.capacity
    }
    return hash
}

func (ht *HashTable) rehash() {
    oldItems := ht.getAllItems()
    ht.capacity *= 2
    ht.items = make([]HashItem, ht.capacity)
    for i := range ht.items {
        ht.items[i] = HashItem{IsEmpty: true}
    }
    ht.size = 0

    for _, item := range oldItems {
        ht.Insert(item.Key, item.Value)
    }
}

func (ht *HashTable) getAllItems() []HashItem {
    result := make([]HashItem, 0, ht.size)
    for i := 0; i < ht.capacity; i++ {
        if !ht.items[i].IsEmpty && !ht.items[i].IsDeleted {
            result = append(result, ht.items[i])
        }
    }
    return result
}