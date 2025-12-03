package main

import (
    "datastructures/structures"
    "bufio"
    "fmt"
    "os"
    "strconv"
    "strings"
)

func main() {
    
    runInteractive()
}

func runInteractive() {
    reader := bufio.NewReader(os.Stdin)
    
    array := structures.NewDynamicArray(5)
    list := structures.NewSinglyLinkedList()
    dlist := structures.NewDoublyLinkedList()
    queue := structures.NewQueue()
    stack := structures.NewStack()
    tree := structures.NewAVLTree()
    hashTable := structures.NewHashTable(10)
    
    for {
        printMenu()
        fmt.Print("Выберите действие: ")
        
        input, _ := reader.ReadString('\n')
        input = strings.TrimSpace(input)
        
        if input == "0" {
            fmt.Println("Выход из программы.")
            break
        }
        
        switch input {
        case "1":
            arrayMenu(array, reader)
        case "2":
            singlyLinkedListMenu(list, reader)
        case "3":
            doublyLinkedListMenu(dlist, reader)
        case "4":
            queueMenu(queue, reader)
        case "5":
            stackMenu(stack, reader)
        case "6":
            treeMenu(tree, reader)
        case "7":
            hashTableMenu(hashTable, reader)
        case "8":
            testAll(array, list, dlist, queue, stack, tree, hashTable)
        default:
            fmt.Println("Неверный выбор. Попробуйте снова.")
        }
    }
}

func printMenu() {
    fmt.Println(" Меню управления структурами данных ")
    fmt.Println("1. Динамический массив")
    fmt.Println("2. Односвязный список")
    fmt.Println("3. Двусвязный список")
    fmt.Println("4. Очередь")
    fmt.Println("5. Стек")
    fmt.Println("6. AVL-дерево")
    fmt.Println("7. Хеш-таблица")
    fmt.Println("8. Тестирование всех структур")
    fmt.Println("0. Выход")
}

func arrayMenu(da *structures.DynamicArray, reader *bufio.Reader) {
    for {
        fmt.Println("\n--- Динамический массив ---")
        da.Print()
        fmt.Println("1. Добавить в конец")
        fmt.Println("2. Вставить по индексу")
        fmt.Println("3. Удалить по индексу")
        fmt.Println("4. Получить элемент")
        fmt.Println("5. Найти элемент")
        fmt.Println("6. Очистить")
        fmt.Println("7. Назад")
        fmt.Print("Выбор: ")
        
        input, _ := reader.ReadString('\n')
        input = strings.TrimSpace(input)
        
        switch input {
        case "1":
            fmt.Print("Введите значение: ")
            value, _ := reader.ReadString('\n')
            da.PushBack(strings.TrimSpace(value))
        case "2":
            fmt.Print("Введите индекс: ")
            idxStr, _ := reader.ReadString('\n')
            idx, _ := strconv.Atoi(strings.TrimSpace(idxStr))
            fmt.Print("Введите значение: ")
            value, _ := reader.ReadString('\n')
            err := da.Insert(idx, strings.TrimSpace(value))
            if err != nil {
                fmt.Println("Ошибка:", err)
            }
        case "3":
            fmt.Print("Введите индекс: ")
            idxStr, _ := reader.ReadString('\n')
            idx, _ := strconv.Atoi(strings.TrimSpace(idxStr))
            val, err := da.Remove(idx)
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Удалено:", val)
            }
        case "4":
            fmt.Print("Введите индекс: ")
            idxStr, _ := reader.ReadString('\n')
            idx, _ := strconv.Atoi(strings.TrimSpace(idxStr))
            val, err := da.Get(idx)
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Элемент:", val)
            }
        case "5":
            fmt.Print("Введите значение для поиска: ")
            value, _ := reader.ReadString('\n')
            idx := da.Find(strings.TrimSpace(value))
            if idx == -1 {
                fmt.Println("Элемент не найден")
            } else {
                fmt.Println("Найден по индексу:", idx)
            }
        case "6":
            da.Clear()
            fmt.Println("Массив очищен")
        case "7":
            return
        default:
            fmt.Println("Неверный выбор")
        }
    }
}

func singlyLinkedListMenu(list *structures.SinglyLinkedList, reader *bufio.Reader) {
    for {
        fmt.Println("\n--- Односвязный список ---")
        list.Print()
        fmt.Println("1. Добавить в начало")
        fmt.Println("2. Добавить в конец")
        fmt.Println("3. Удалить из начала")
        fmt.Println("4. Найти элемент")
        fmt.Println("5. Удалить по значению")
        fmt.Println("6. Получить по индексу")
        fmt.Println("7. Очистить")
        fmt.Println("8. Назад")
        fmt.Print("Выбор: ")
        
        input, _ := reader.ReadString('\n')
        input = strings.TrimSpace(input)
        
        switch input {
        case "1":
            fmt.Print("Введите значение: ")
            value, _ := reader.ReadString('\n')
            list.PushFront(strings.TrimSpace(value))
        case "2":
            fmt.Print("Введите значение: ")
            value, _ := reader.ReadString('\n')
            list.PushBack(strings.TrimSpace(value))
        case "3":
            val, err := list.PopFront()
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Удалено:", val)
            }
        case "4":
            fmt.Print("Введите значение для поиска: ")
            value, _ := reader.ReadString('\n')
            node := list.Find(strings.TrimSpace(value))
            if node == nil {
                fmt.Println("Элемент не найден")
            } else {
                fmt.Println("Элемент найден")
            }
        case "5":
            fmt.Print("Введите значение для удаления: ")
            value, _ := reader.ReadString('\n')
            if list.DeleteByKey(strings.TrimSpace(value)) {
                fmt.Println("Элемент удален")
            } else {
                fmt.Println("Элемент не найден")
            }
        case "6":
            fmt.Print("Введите индекс: ")
            idxStr, _ := reader.ReadString('\n')
            idx, _ := strconv.Atoi(strings.TrimSpace(idxStr))
            val, err := list.GetAt(idx)
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Элемент:", val)
            }
        case "7":
            list.Clear()
            fmt.Println("Список очищен")
        case "8":
            return
        default:
            fmt.Println("Неверный выбор")
        }
    }
}

func doublyLinkedListMenu(dlist *structures.DoublyLinkedList, reader *bufio.Reader) {
    for {
        fmt.Println("\n--- Двусвязный список ---")
        dlist.Print()
        fmt.Println("1. Добавить в начало")
        fmt.Println("2. Добавить в конец")
        fmt.Println("3. Удалить из начала")
        fmt.Println("4. Удалить из конца")
        fmt.Println("5. Найти элемент")
        fmt.Println("6. Удалить по значению")
        fmt.Println("7. Показать в обратном порядке")
        fmt.Println("8. Очистить")
        fmt.Println("9. Назад")
        fmt.Print("Выбор: ")
        
        input, _ := reader.ReadString('\n')
        input = strings.TrimSpace(input)
        
        switch input {
        case "1":
            fmt.Print("Введите значение: ")
            value, _ := reader.ReadString('\n')
            dlist.PushFront(strings.TrimSpace(value))
        case "2":
            fmt.Print("Введите значение: ")
            value, _ := reader.ReadString('\n')
            dlist.PushBack(strings.TrimSpace(value))
        case "3":
            val, err := dlist.PopFront()
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Удалено:", val)
            }
        case "4":
            val, err := dlist.PopBack()
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Удалено:", val)
            }
        case "5":
            fmt.Print("Введите значение для поиска: ")
            value, _ := reader.ReadString('\n')
            node := dlist.Find(strings.TrimSpace(value))
            if node == nil {
                fmt.Println("Элемент не найден")
            } else {
                fmt.Println("Элемент найден")
            }
        case "6":
            fmt.Print("Введите значение для удаления: ")
            value, _ := reader.ReadString('\n')
            if dlist.DeleteByKey(strings.TrimSpace(value)) {
                fmt.Println("Элемент удален")
            } else {
                fmt.Println("Элемент не найден")
            }
        case "7":
            dlist.PrintReverse()
        case "8":
            dlist.Clear()
            fmt.Println("Список очищен")
        case "9":
            return
        default:
            fmt.Println("Неверный выбор")
        }
    }
}

func queueMenu(queue *structures.Queue, reader *bufio.Reader) {
    for {
        fmt.Println("\n--- Очередь ---")
        queue.Print()
        fmt.Println("1. Добавить в очередь")
        fmt.Println("2. Извлечь из очереди")
        fmt.Println("3. Показать первый элемент")
        fmt.Println("4. Показать последний элемент")
        fmt.Println("5. Очистить")
        fmt.Println("6. Назад")
        fmt.Print("Выбор: ")
        
        input, _ := reader.ReadString('\n')
        input = strings.TrimSpace(input)
        
        switch input {
        case "1":
            fmt.Print("Введите значение: ")
            value, _ := reader.ReadString('\n')
            queue.Push(strings.TrimSpace(value))
        case "2":
            val, err := queue.Pop()
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Извлечено:", val)
            }
        case "3":
            val, err := queue.Front()
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Первый элемент:", val)
            }
        case "4":
            val, err := queue.Rear()
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Последний элемент:", val)
            }
        case "5":
            queue.Clear()
            fmt.Println("Очередь очищена")
        case "6":
            return
        default:
            fmt.Println("Неверный выбор")
        }
    }
}

func stackMenu(stack *structures.Stack, reader *bufio.Reader) {
    for {
        fmt.Println("\n--- Стек ---")
        stack.Print()
        fmt.Println("1. Добавить в стек")
        fmt.Println("2. Извлечь из стека")
        fmt.Println("3. Показать верхний элемент")
        fmt.Println("4. Очистить")
        fmt.Println("5. Назад")
        fmt.Print("Выбор: ")
        
        input, _ := reader.ReadString('\n')
        input = strings.TrimSpace(input)
        
        switch input {
        case "1":
            fmt.Print("Введите значение: ")
            value, _ := reader.ReadString('\n')
            stack.Push(strings.TrimSpace(value))
        case "2":
            val, err := stack.Pop()
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Извлечено:", val)
            }
        case "3":
            val, err := stack.Top()
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Верхний элемент:", val)
            }
        case "4":
            stack.Clear()
            fmt.Println("Стек очищен")
        case "5":
            return
        default:
            fmt.Println("Неверный выбор")
        }
    }
}

func treeMenu(tree *structures.AVLTree, reader *bufio.Reader) {
    for {
        fmt.Println("\n--- AVL-дерево ---")
        fmt.Println("Размер дерева:", tree.Size())
        fmt.Println("1. Добавить элемент")
        fmt.Println("2. Поиск элемента")
        fmt.Println("3. Удалить элемент")
        fmt.Println("4. Показать минимальный элемент")
        fmt.Println("5. Показать максимальный элемент")
        fmt.Println("6. Показать inorder")
        fmt.Println("7. Показать preorder")
        fmt.Println("8. Показать postorder")
        fmt.Println("9. Очистить")
        fmt.Println("10. Назад")
        fmt.Print("Выбор: ")
        
        input, _ := reader.ReadString('\n')
        input = strings.TrimSpace(input)
        
        switch input {
        case "1":
            fmt.Print("Введите целое число: ")
            valueStr, _ := reader.ReadString('\n')
            value, err := strconv.Atoi(strings.TrimSpace(valueStr))
            if err != nil {
                fmt.Println("Ошибка: введите целое число")
            } else {
                tree.Insert(value)
                fmt.Println("Элемент добавлен")
            }
        case "2":
            fmt.Print("Введите целое число для поиска: ")
            valueStr, _ := reader.ReadString('\n')
            value, err := strconv.Atoi(strings.TrimSpace(valueStr))
            if err != nil {
                fmt.Println("Ошибка: введите целое число")
            } else {
                if tree.Search(value) {
                    fmt.Println("Элемент найден")
                } else {
                    fmt.Println("Элемент не найден")
                }
            }
        case "3":
            fmt.Print("Введите целое число для удаления: ")
            valueStr, _ := reader.ReadString('\n')
            value, err := strconv.Atoi(strings.TrimSpace(valueStr))
            if err != nil {
                fmt.Println("Ошибка: введите целое число")
            } else {
                tree.Remove(value)
                fmt.Println("Элемент удален (если существовал)")
            }
        case "4":
            val, err := tree.Min()
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Минимальный элемент:", val)
            }
        case "5":
            val, err := tree.Max()
            if err != nil {
                fmt.Println("Ошибка:", err)
            } else {
                fmt.Println("Максимальный элемент:", val)
            }
        case "6":
            tree.PrintInOrder()
        case "7":
            tree.PrintPreOrder()
        case "8":
            tree.PrintPostOrder()
        case "9":
            tree.Clear()
            fmt.Println("Дерево очищено")
        case "10":
            return
        default:
            fmt.Println("Неверный выбор")
        }
    }
}

func hashTableMenu(hashTable *structures.HashTable, reader *bufio.Reader) {
    for {
        fmt.Println("\n--- Хеш-таблица ---")
        hashTable.Print()
        fmt.Println("1. Добавить/обновить элемент")
        fmt.Println("2. Найти элемент")
        fmt.Println("3. Удалить элемент")
        fmt.Println("4. Очистить")
        fmt.Println("5. Назад")
        fmt.Print("Выбор: ")
        
        input, _ := reader.ReadString('\n')
        input = strings.TrimSpace(input)
        
        switch input {
        case "1":
            fmt.Print("Введите ключ: ")
            key, _ := reader.ReadString('\n')
            key = strings.TrimSpace(key)
            fmt.Print("Введите значение: ")
            value, _ := reader.ReadString('\n')
            value = strings.TrimSpace(value)
            if hashTable.Insert(key, value) {
                fmt.Println("Элемент добавлен/обновлен")
            } else {
                fmt.Println("Ошибка при добавлении")
            }
        case "2":
            fmt.Print("Введите ключ: ")
            key, _ := reader.ReadString('\n')
            key = strings.TrimSpace(key)
            value, found := hashTable.Find(key)
            if found {
                fmt.Println("Найдено:", value)
            } else {
                fmt.Println("Ключ не найден")
            }
        case "3":
            fmt.Print("Введите ключ: ")
            key, _ := reader.ReadString('\n')
            key = strings.TrimSpace(key)
            if hashTable.Remove(key) {
                fmt.Println("Элемент удален")
            } else {
                fmt.Println("Ключ не найден")
            }
        case "4":
            hashTable.Clear()
            fmt.Println("Хеш-таблица очищена")
        case "5":
            return
        default:
            fmt.Println("Неверный выбор")
        }
    }
}

func testAll(array *structures.DynamicArray, list *structures.SinglyLinkedList,
            dlist *structures.DoublyLinkedList, queue *structures.Queue,
            stack *structures.Stack, tree *structures.AVLTree,
            hashTable *structures.HashTable) {
    
    fmt.Println("\n=== Тестирование всех структур ===")
    
    fmt.Println("\n1. Динамический массив:")
    array.Print()
    
    fmt.Println("\n2. Односвязный список:")
    list.Print()
    
    fmt.Println("\n3. Двусвязный список:")
    dlist.Print()
    
    fmt.Println("\n4. Очередь:")
    queue.Print()
    
    fmt.Println("\n5. Стек:")
    stack.Print()
    
    fmt.Println("\n6. AVL-дерево:")
    tree.PrintInOrder()
    
    fmt.Println("\n7. Хеш-таблица:")
    hashTable.Print()
    
    fmt.Println("\n=== Тестирование завершено ===")
}