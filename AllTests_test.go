package structures

import (
    "fmt"
    "testing"
    "github.com/stretchr/testify/assert"
)

func TestDynamicArray(t *testing.T) {
    da := NewDynamicArray(5)

    t.Run("PushBack and Size", func(t *testing.T) {
        da.PushBack("first")
        da.PushBack("second")
        assert.Equal(t, 2, da.Size())
        assert.Equal(t, 5, da.Capacity())
    })

    t.Run("Get and Set", func(t *testing.T) {
        val, err := da.Get(0)
        assert.NoError(t, err)
        assert.Equal(t, "first", val)

        err = da.Set(1, "modified")
        assert.NoError(t, err)
        
        val, err = da.Get(1)
        assert.NoError(t, err)
        assert.Equal(t, "modified", val)
    })

    t.Run("Insert", func(t *testing.T) {
        err := da.Insert(1, "middle")
        assert.NoError(t, err)
        assert.Equal(t, 3, da.Size())
        
        val, err := da.Get(1)
        assert.NoError(t, err)
        assert.Equal(t, "middle", val)
    })

    t.Run("Remove", func(t *testing.T) {
        val, err := da.Remove(1)
        assert.NoError(t, err)
        assert.Equal(t, "middle", val)
        assert.Equal(t, 2, da.Size())
    })

    t.Run("Find", func(t *testing.T) {
        index := da.Find("first")
        assert.Equal(t, 0, index)
        
        index = da.Find("nonexistent")
        assert.Equal(t, -1, index)
    })

    t.Run("Serialization", func(t *testing.T) {
        data := da.Serialize()
        assert.Equal(t, []string{"first", "modified"}, data)
        
        newDa := NewDynamicArray(2)
        newDa.Deserialize(data)
        assert.Equal(t, da.Size(), newDa.Size())
        
        val, err := newDa.Get(0)
        assert.NoError(t, err)
        assert.Equal(t, "first", val)
    })

    t.Run("Clear", func(t *testing.T) {
        da.Clear()
        assert.Equal(t, 0, da.Size())
        assert.Equal(t, 5, da.Capacity())
    })

    t.Run("Edge cases", func(t *testing.T) {
        _, err := da.Get(-1)
        assert.Error(t, err)
        
        _, err = da.Get(100)
        assert.Error(t, err)
        
        err = da.Set(-1, "value")
        assert.Error(t, err)
        
        _, err = da.Remove(-1)
        assert.Error(t, err)
        
        err = da.Insert(-1, "value")
        assert.Error(t, err)
    })

    t.Run("Capacity expansion", func(t *testing.T) {
        largeDa := NewDynamicArray(2)
        for i := 0; i < 10; i++ {
            largeDa.PushBack("item")
        }
        assert.True(t, largeDa.Capacity() >= 10)
        assert.Equal(t, 10, largeDa.Size())
    })

    t.Run("Print method", func(t *testing.T) {
        da := NewDynamicArray(3)
        da.PushBack("A")
        da.PushBack("B")
        assert.NotPanics(t, func() { da.Print() })
    })

    t.Run("Initial capacity edge cases", func(t *testing.T) {
        da1 := NewDynamicArray(0)
        assert.True(t, da1.Capacity() > 0)
        
        da2 := NewDynamicArray(-5)
        assert.True(t, da2.Capacity() > 0)
    })
}

func TestSinglyLinkedList(t *testing.T) {
    list := NewSinglyLinkedList()

    t.Run("PushFront and PushBack", func(t *testing.T) {
        list.PushFront("first")
        list.PushBack("last")
        assert.Equal(t, 2, list.Size())
    })

    t.Run("Find", func(t *testing.T) {
        node := list.Find("first")
        assert.NotNil(t, node)
        assert.Equal(t, "first", node.Value)
        
        node = list.Find("nonexistent")
        assert.Nil(t, node)
    })

    t.Run("AddAfter and DeleteAfter", func(t *testing.T) {
        node := list.Find("first")
        assert.NotNil(t, node)
        
        err := list.AddAfter(node, "middle")
        assert.NoError(t, err)
        assert.Equal(t, 3, list.Size())
        
        err = list.DeleteAfter(node)
        assert.NoError(t, err)
        assert.Equal(t, 2, list.Size())
    })

    t.Run("AddBefore and DeleteBefore", func(t *testing.T) {
        node := list.Find("last")
        assert.NotNil(t, node)
        
        err := list.AddBefore(node, "beforeLast")
        assert.NoError(t, err)
        assert.Equal(t, 3, list.Size())
        
        err = list.DeleteBefore(node)
        assert.NoError(t, err)
        assert.Equal(t, 2, list.Size())
    })

    t.Run("PopFront", func(t *testing.T) {
        val, err := list.PopFront()
        assert.NoError(t, err)
        assert.Equal(t, "first", val)
        assert.Equal(t, 1, list.Size())
    })

    t.Run("GetAt", func(t *testing.T) {
        list.PushFront("newFirst")
        val, err := list.GetAt(0)
        assert.NoError(t, err)
        assert.Equal(t, "newFirst", val)
        
        _, err = list.GetAt(10)
        assert.Error(t, err)
    })

    t.Run("Serialization", func(t *testing.T) {
        data := list.Serialize()
        assert.Equal(t, []string{"newFirst", "last"}, data)
        
        newList := NewSinglyLinkedList()
        newList.Deserialize(data)
        assert.Equal(t, list.Size(), newList.Size())
        
        val, err := newList.GetAt(0)
        assert.NoError(t, err)
        assert.Equal(t, "newFirst", val)
    })

    t.Run("Clear", func(t *testing.T) {
        list.Clear()
        assert.Equal(t, 0, list.Size())
        assert.Nil(t, list.Find("any"))
    })

    t.Run("Edge cases", func(t *testing.T) {
        err := list.AddAfter(nil, "test")
        assert.Error(t, err)
        
        err = list.AddBefore(nil, "test")
        assert.Error(t, err)
        
        err = list.DeleteAfter(nil)
        assert.Error(t, err)
        
        err = list.DeleteBefore(nil)
        assert.Error(t, err)
        
        _, err = list.PopFront()
        assert.Error(t, err)
    })

    t.Run("DeleteByKey", func(t *testing.T) {
        list.Clear()
        list.PushBack("A")
        list.PushBack("B")
        list.PushBack("C")
        
        assert.False(t, list.DeleteByKey("nonexistent"))
        assert.True(t, list.DeleteByKey("B"))
        assert.Equal(t, 2, list.Size())
        assert.Nil(t, list.Find("B"))
        
        assert.True(t, list.DeleteByKey("A"))
        assert.Equal(t, 1, list.Size())
        
        assert.True(t, list.DeleteByKey("C"))
        assert.Equal(t, 0, list.Size())
    })

    t.Run("Print method", func(t *testing.T) {
        list.Clear()
        list.PushBack("X")
        list.PushBack("Y")
        assert.NotPanics(t, func() { list.Print() })
    })

    t.Run("GetHead method", func(t *testing.T) {
        list.Clear()
        assert.Nil(t, list.GetHead())
        
        list.PushBack("test")
        assert.NotNil(t, list.GetHead())
        assert.Equal(t, "test", list.GetHead().Value)
    })
}

func TestDoublyLinkedList(t *testing.T) {
    list := NewDoublyLinkedList()

    t.Run("PushFront and PushBack", func(t *testing.T) {
        list.PushFront("B")
        list.PushFront("A")
        list.PushBack("C")
        assert.Equal(t, 3, list.Size())
    })

    t.Run("Find", func(t *testing.T) {
        node := list.Find("B")
        assert.NotNil(t, node)
        assert.Equal(t, "B", node.Value)
        
        node = list.Find("nonexistent")
        assert.Nil(t, node)
    })

    t.Run("AddAfter and AddBefore", func(t *testing.T) {
        node := list.Find("B")
        assert.NotNil(t, node)
        
        err := list.AddAfter(node, "B2")
        assert.NoError(t, err)
        assert.Equal(t, 4, list.Size())
        
        err = list.AddBefore(node, "A2")
        assert.NoError(t, err)
        assert.Equal(t, 5, list.Size())
    })

    t.Run("DeleteAfter and DeleteBefore", func(t *testing.T) {
        node := list.Find("B")
        assert.NotNil(t, node)
        
        err := list.DeleteAfter(node)
        assert.NoError(t, err)
        assert.Equal(t, 4, list.Size())
        
        err = list.DeleteBefore(node)
        assert.NoError(t, err)
        assert.Equal(t, 3, list.Size())
    })

    t.Run("PopFront and PopBack", func(t *testing.T) {
        val, err := list.PopFront()
        assert.NoError(t, err)
        assert.Equal(t, "A", val)
        assert.Equal(t, 2, list.Size())
        
        val, err = list.PopBack()
        assert.NoError(t, err)
        assert.Equal(t, "C", val)
        assert.Equal(t, 1, list.Size())
    })

    t.Run("DeleteByKey", func(t *testing.T) {
        list.PushBack("X")
        list.PushBack("Y")
        assert.True(t, list.DeleteByKey("B"))
        assert.False(t, list.DeleteByKey("nonexistent"))
        assert.Equal(t, 2, list.Size())
    })

    t.Run("GetAt", func(t *testing.T) {
        val, err := list.GetAt(0)
        assert.NoError(t, err)
        assert.Equal(t, "X", val)
        
        _, err = list.GetAt(10)
        assert.Error(t, err)
    })

    t.Run("Serialization", func(t *testing.T) {
        data := list.Serialize()
        assert.Equal(t, []string{"X", "Y"}, data)
        
        newList := NewDoublyLinkedList()
        newList.Deserialize(data)
        assert.Equal(t, list.Size(), newList.Size())
        
        val, err := newList.GetAt(0)
        assert.NoError(t, err)
        assert.Equal(t, "X", val)
    })

    t.Run("Clear", func(t *testing.T) {
        list.Clear()
        assert.Equal(t, 0, list.Size())
        assert.Nil(t, list.Find("any"))
    })

    t.Run("Edge cases", func(t *testing.T) {
        err := list.AddAfter(nil, "test")
        assert.Error(t, err)
        
        err = list.AddBefore(nil, "test")
        assert.Error(t, err)
        
        err = list.DeleteAfter(nil)
        assert.Error(t, err)
        
        err = list.DeleteBefore(nil)
        assert.Error(t, err)
        
        _, err = list.PopFront()
        assert.Error(t, err)
        
        _, err = list.PopBack()
        assert.Error(t, err)
    })

    t.Run("Print methods", func(t *testing.T) {
        list.Clear()
        list.PushBack("A")
        list.PushBack("B")
        assert.NotPanics(t, func() { list.Print() })
        assert.NotPanics(t, func() { list.PrintReverse() })
    })

    t.Run("GetHead and GetTail", func(t *testing.T) {
        list.Clear()
        assert.Nil(t, list.GetHead())
        assert.Nil(t, list.GetTail())
        
        list.PushBack("head")
        list.PushBack("tail")
        assert.NotNil(t, list.GetHead())
        assert.NotNil(t, list.GetTail())
        assert.Equal(t, "head", list.GetHead().Value)
        assert.Equal(t, "tail", list.GetTail().Value)
    })
}

func TestQueue(t *testing.T) {
    queue := NewQueue()

    t.Run("Push and basic operations", func(t *testing.T) {
        assert.True(t, queue.Empty())
        
        queue.Push("A")
        queue.Push("B")
        queue.Push("C")
        assert.Equal(t, 3, queue.Size())
    })

    t.Run("Pop", func(t *testing.T) {
        val, err := queue.Pop()
        assert.NoError(t, err)
        assert.Equal(t, "A", val)
        
        val, err = queue.Pop()
        assert.NoError(t, err)
        assert.Equal(t, "B", val)
        
        val, err = queue.Pop()
        assert.NoError(t, err)
        assert.Equal(t, "C", val)
        
        assert.True(t, queue.Empty())
    })

    t.Run("Empty queue errors", func(t *testing.T) {
        _, err := queue.Pop()
        assert.Error(t, err)
    })

    t.Run("Serialization", func(t *testing.T) {
        queue.Push("X")
        queue.Push("Y")
        data := queue.Serialize()
        
        newQueue := NewQueue()
        newQueue.Deserialize(data)
        assert.Equal(t, 2, newQueue.Size())
        
        val, err := newQueue.Pop()
        assert.NoError(t, err)
        assert.Equal(t, "X", val)
    })

    t.Run("Clear", func(t *testing.T) {
        queue.Clear()
        assert.True(t, queue.Empty())
        assert.Equal(t, 0, queue.Size())
    })

    t.Run("Front and Rear methods", func(t *testing.T) {
        queue.Clear()
        
        // Test empty queue
        _, err := queue.Front()
        assert.Error(t, err)
        _, err = queue.Rear()
        assert.Error(t, err)
        
        // Test with elements
        queue.Push("first")
        queue.Push("last")
        
        front, err := queue.Front()
        assert.NoError(t, err)
        assert.Equal(t, "first", front)
        
        rear, err := queue.Rear()
        assert.NoError(t, err)
        assert.Equal(t, "last", rear)
    })

    t.Run("Print method", func(t *testing.T) {
        queue.Clear()
        queue.Push("A")
        queue.Push("B")
        assert.NotPanics(t, func() { queue.Print() })
    })
}

func TestStack(t *testing.T) {
    stack := NewStack()

    t.Run("Push and basic operations", func(t *testing.T) {
        assert.True(t, stack.Empty())
        
        stack.Push("A")
        stack.Push("B")
        stack.Push("C")
        assert.Equal(t, 3, stack.Size())
    })

    t.Run("Pop", func(t *testing.T) {
        val, err := stack.Pop()
        assert.NoError(t, err)
        assert.Equal(t, "C", val)
        
        val, err = stack.Pop()
        assert.NoError(t, err)
        assert.Equal(t, "B", val)
        
        val, err = stack.Pop()
        assert.NoError(t, err)
        assert.Equal(t, "A", val)
        
        assert.True(t, stack.Empty())
    })

    t.Run("Empty stack errors", func(t *testing.T) {
        _, err := stack.Pop()
        assert.Error(t, err)
    })

    t.Run("Serialization", func(t *testing.T) {
        stack.Push("X")
        stack.Push("Y")
        data := stack.Serialize()
        
        newStack := NewStack()
        newStack.Deserialize(data)
        assert.Equal(t, 2, newStack.Size())
    })

    t.Run("Clear", func(t *testing.T) {
        stack.Clear()
        assert.True(t, stack.Empty())
        assert.Equal(t, 0, stack.Size())
    })

    t.Run("Top method", func(t *testing.T) {
        stack.Clear()
        
        // Test empty stack
        _, err := stack.Top()
        assert.Error(t, err)
        
        // Test with elements
        stack.Push("bottom")
        stack.Push("top")
        
        top, err := stack.Top()
        assert.NoError(t, err)
        assert.Equal(t, "top", top)
        
        // Make sure Top doesn't remove element
        assert.Equal(t, 2, stack.Size())
    })

    t.Run("Print method", func(t *testing.T) {
        stack.Clear()
        stack.Push("A")
        stack.Push("B")
        assert.NotPanics(t, func() { stack.Print() })
    })
}

func TestAVLTree(t *testing.T) {
    tree := NewAVLTree()

    t.Run("Insert and basic operations", func(t *testing.T) {
        assert.True(t, tree.Empty())
        
        tree.Insert(50)
        tree.Insert(30)
        tree.Insert(70)
        tree.Insert(20)
        tree.Insert(40)
        tree.Insert(60)
        tree.Insert(80)
        
        assert.Equal(t, 7, tree.Size())
        assert.False(t, tree.Empty())
    })

    t.Run("Search", func(t *testing.T) {
        assert.True(t, tree.Search(50))
        assert.True(t, tree.Search(20))
        assert.True(t, tree.Search(80))
        assert.False(t, tree.Search(100))
    })

    t.Run("Min and Max", func(t *testing.T) {
        min, err := tree.Min()
        assert.NoError(t, err)
        assert.Equal(t, 20, min)
        
        max, err := tree.Max()
        assert.NoError(t, err)
        assert.Equal(t, 80, max)
    })

    t.Run("Remove", func(t *testing.T) {
        tree.Remove(50)
        tree.Remove(20)
        tree.Remove(80)
        
        assert.Equal(t, 4, tree.Size())
        assert.False(t, tree.Search(50))
        assert.False(t, tree.Search(20))
        assert.False(t, tree.Search(80))
    })

    t.Run("Empty tree", func(t *testing.T) {
        emptyTree := NewAVLTree()
        assert.True(t, emptyTree.Empty())
        
        _, err := emptyTree.Min()
        assert.Error(t, err)
        
        _, err = emptyTree.Max()
        assert.Error(t, err)
        
        assert.Equal(t, 0, emptyTree.Size())
        assert.Equal(t, 0, emptyTree.Height())
    })

    t.Run("Serialization", func(t *testing.T) {
        data := tree.Serialize()
        assert.True(t, len(data) > 0)
        
        newTree := NewAVLTree()
        newTree.Deserialize(data)
        assert.Equal(t, tree.Size(), newTree.Size())
    })

    t.Run("Traversal orders", func(t *testing.T) {
        tree.Clear()
        tree.Insert(50)
        tree.Insert(30)
        tree.Insert(70)
        tree.Insert(20)
        tree.Insert(40)
        
        inOrder := tree.InOrder()
        preOrder := tree.PreOrder()
        postOrder := tree.PostOrder()
        
        assert.True(t, len(inOrder) > 0)
        assert.True(t, len(preOrder) > 0)
        assert.True(t, len(postOrder) > 0)
    })

    t.Run("Balance property", func(t *testing.T) {
        tree.Clear()
        for i := 1; i <= 100; i++ {
            tree.Insert(i)
        }
        
        height := tree.Height()
        assert.True(t, height <= 14)
        assert.Equal(t, 100, tree.Size())
    })

    t.Run("Print methods", func(t *testing.T) {
        tree.Clear()
        tree.Insert(50)
        tree.Insert(30)
        tree.Insert(70)
        assert.NotPanics(t, func() { tree.PrintInOrder() })
        assert.NotPanics(t, func() { tree.PrintPreOrder() })
        assert.NotPanics(t, func() { tree.PrintPostOrder() })
    })

    t.Run("Rotations and edge cases", func(t *testing.T) {
        tree.Clear()
        
        // Test left rotation
        tree.Insert(10)
        tree.Insert(20)
        tree.Insert(30)
        assert.Equal(t, 3, tree.Size())
        
        // Test right rotation
        tree2 := NewAVLTree()
        tree2.Insert(30)
        tree2.Insert(20)
        tree2.Insert(10)
        assert.Equal(t, 3, tree2.Size())
        
        // Test duplicate insertion
        tree3 := NewAVLTree()
        tree3.Insert(10)
        tree3.Insert(10)
        assert.Equal(t, 1, tree3.Size())
    })
}

func TestHashTable(t *testing.T) {
    table := NewHashTable(5)

    t.Run("Insert and basic operations", func(t *testing.T) {
        table.Insert("key1", "value1")
        table.Insert("key2", "value2")
        table.Insert("key3", "value3")
        table.Insert("key4", "value4")
        table.Insert("key5", "value5")
        table.Insert("key6", "value6")
        
        assert.True(t, table.Capacity() > 5)
        assert.Equal(t, 6, table.Size())
    })

    t.Run("Find", func(t *testing.T) {
        value, found := table.Find("key1")
        assert.True(t, found)
        assert.Equal(t, "value1", value)
        
        value, found = table.Find("key6")
        assert.True(t, found)
        assert.Equal(t, "value6", value)
    })

    t.Run("Update value", func(t *testing.T) {
        table.Insert("key1", "newvalue1")
        value, found := table.Find("key1")
        assert.True(t, found)
        assert.Equal(t, "newvalue1", value)
    })

    t.Run("Remove", func(t *testing.T) {
        removed := table.Remove("key1")
        assert.True(t, removed)
        
        _, found := table.Find("key1")
        assert.False(t, found)
        assert.Equal(t, 5, table.Size())
    })

    t.Run("Non-existent key", func(t *testing.T) {
        removed := table.Remove("nonexistent")
        assert.False(t, removed)
        
        _, found := table.Find("nonexistent")
        assert.False(t, found)
    })

    t.Run("Clear", func(t *testing.T) {
        table.Clear()
        assert.True(t, table.Empty())
        assert.Equal(t, 0, table.Size())
    })

    t.Run("Serialization", func(t *testing.T) {
        table.Insert("x", "y")
        table.Insert("a", "b")
        data := table.Serialize()
        
        newTable := NewHashTable(2)
        newTable.Deserialize(data)
        assert.Equal(t, 2, newTable.Size())
        
        value, found := newTable.Find("x")
        assert.True(t, found)
        assert.Equal(t, "y", value)
    })

    t.Run("Collision handling", func(t *testing.T) {
        collisionTable := NewHashTable(3)
        collisionTable.Insert("abc", "1")
        collisionTable.Insert("def", "2")
        collisionTable.Insert("ghi", "3")
        collisionTable.Insert("jkl", "4")
        
        value, found := collisionTable.Find("abc")
        assert.True(t, found)
        assert.Equal(t, "1", value)
        
        value, found = collisionTable.Find("def")
        assert.True(t, found)
        assert.Equal(t, "2", value)
        
        value, found = collisionTable.Find("ghi")
        assert.True(t, found)
        assert.Equal(t, "3", value)
        
        value, found = collisionTable.Find("jkl")
        assert.True(t, found)
        assert.Equal(t, "4", value)
        
        collisionTable.Remove("def")
        _, found = collisionTable.Find("def")
        assert.False(t, found)
        
        value, found = collisionTable.Find("abc")
        assert.True(t, found)
        assert.Equal(t, "1", value)
    })

    t.Run("Rehashing", func(t *testing.T) {
        smallTable := NewHashTable(3)
        // Force rehashing by adding many elements
        for i := 0; i < 10; i++ {
            key := fmt.Sprintf("key%d", i)
            value := fmt.Sprintf("value%d", i)
            assert.True(t, smallTable.Insert(key, value))
        }
        assert.True(t, smallTable.Capacity() > 3)
        assert.Equal(t, 10, smallTable.Size())
    })

    t.Run("Print method", func(t *testing.T) {
        table := NewHashTable(5)
        table.Insert("test1", "value1")
        table.Insert("test2", "value2")
        assert.NotPanics(t, func() { table.Print() })
    })

    t.Run("Initial capacity edge cases", func(t *testing.T) {
        table1 := NewHashTable(0)
        assert.True(t, table1.Capacity() > 0)
        
        table2 := NewHashTable(-5)
        assert.True(t, table2.Capacity() > 0)
    })
}