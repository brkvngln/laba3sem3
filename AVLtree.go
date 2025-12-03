package structures

import (
    "fmt"
    "strconv"
)

type TreeNode struct {
    Value  int
    Left   *TreeNode
    Right  *TreeNode
    Height int
}

type AVLTree struct {
    root *TreeNode
}

func NewAVLTree() *AVLTree {
    return &AVLTree{root: nil}
}

func (t *AVLTree) Insert(value int) {
    t.root = t.insertNode(t.root, value)
}

func (t *AVLTree) Search(value int) bool {
    return t.searchNode(t.root, value)
}

func (t *AVLTree) Remove(value int) {
    t.root = t.deleteNode(t.root, value)
}

func (t *AVLTree) Empty() bool {
    return t.root == nil
}

func (t *AVLTree) Size() int {
    return t.countNodes(t.root)
}

func (t *AVLTree) Height() int {
    return t.getHeight(t.root)
}

func (t *AVLTree) Min() (int, error) {
    if t.root == nil {
        return 0, fmt.Errorf("tree is empty")
    }
    return t.findMin(t.root), nil
}

func (t *AVLTree) Max() (int, error) {
    if t.root == nil {
        return 0, fmt.Errorf("tree is empty")
    }
    return t.findMax(t.root), nil
}

func (t *AVLTree) InOrder() []int {
    result := make([]int, 0)
    t.inOrderCollect(t.root, &result)
    return result
}

func (t *AVLTree) PreOrder() []int {
    result := make([]int, 0)
    t.preOrderCollect(t.root, &result)
    return result
}

func (t *AVLTree) PostOrder() []int {
    result := make([]int, 0)
    t.postOrderCollect(t.root, &result)
    return result
}

func (t *AVLTree) PrintInOrder() {
    fmt.Print("Дерево (inorder): ")
    t.inOrderTraversal(t.root)
    fmt.Println()
}

func (t *AVLTree) PrintPreOrder() {
    fmt.Print("Дерево (preorder): ")
    t.preOrderTraversal(t.root)
    fmt.Println()
}

func (t *AVLTree) PrintPostOrder() {
    fmt.Print("Дерево (postorder): ")
    t.postOrderTraversal(t.root)
    fmt.Println()
}

func (t *AVLTree) Clear() {
    t.root = nil
}

func (t *AVLTree) Serialize() []string {
    result := make([]string, 0)
    t.inOrderSerialize(t.root, &result)
    return result
}

func (t *AVLTree) Deserialize(data []string) {
    t.Clear()
    for _, item := range data {
        if value, err := strconv.Atoi(item); err == nil {
            t.Insert(value)
        }
    }
}

func (t *AVLTree) getHeight(node *TreeNode) int {
    if node == nil {
        return 0
    }
    return node.Height
}

func (t *AVLTree) getBalance(node *TreeNode) int {
    if node == nil {
        return 0
    }
    return t.getHeight(node.Left) - t.getHeight(node.Right)
}

func (t *AVLTree) rightRotate(y *TreeNode) *TreeNode {
    x := y.Left
    T2 := x.Right

    x.Right = y
    y.Left = T2

    y.Height = max(t.getHeight(y.Left), t.getHeight(y.Right)) + 1
    x.Height = max(t.getHeight(x.Left), t.getHeight(x.Right)) + 1

    return x
}

func (t *AVLTree) leftRotate(x *TreeNode) *TreeNode {
    y := x.Right
    T2 := y.Left

    y.Left = x
    x.Right = T2

    x.Height = max(t.getHeight(x.Left), t.getHeight(x.Right)) + 1
    y.Height = max(t.getHeight(y.Left), t.getHeight(y.Right)) + 1

    return y
}

func (t *AVLTree) insertNode(node *TreeNode, value int) *TreeNode {
    if node == nil {
        return &TreeNode{Value: value, Height: 1}
    }

    if value < node.Value {
        node.Left = t.insertNode(node.Left, value)
    } else if value > node.Value {
        node.Right = t.insertNode(node.Right, value)
    } else {
        return node
    }

    node.Height = 1 + max(t.getHeight(node.Left), t.getHeight(node.Right))
    balance := t.getBalance(node)

    if balance > 1 && value < node.Left.Value {
        return t.rightRotate(node)
    }

    if balance < -1 && value > node.Right.Value {
        return t.leftRotate(node)
    }

    if balance > 1 && value > node.Left.Value {
        node.Left = t.leftRotate(node.Left)
        return t.rightRotate(node)
    }

    if balance < -1 && value < node.Right.Value {
        node.Right = t.rightRotate(node.Right)
        return t.leftRotate(node)
    }

    return node
}

func (t *AVLTree) deleteNode(node *TreeNode, value int) *TreeNode {
    if node == nil {
        return node
    }

    if value < node.Value {
        node.Left = t.deleteNode(node.Left, value)
    } else if value > node.Value {
        node.Right = t.deleteNode(node.Right, value)
    } else {
        if node.Left == nil || node.Right == nil {
            var temp *TreeNode
            if node.Left != nil {
                temp = node.Left
            } else {
                temp = node.Right
            }

            if temp == nil {
                temp = node
                node = nil
            } else {
                *node = *temp
            }
        } else {
            temp := t.minValueNode(node.Right)
            node.Value = temp.Value
            node.Right = t.deleteNode(node.Right, temp.Value)
        }
    }

    if node == nil {
        return node
    }

    node.Height = 1 + max(t.getHeight(node.Left), t.getHeight(node.Right))
    balance := t.getBalance(node)

    if balance > 1 && t.getBalance(node.Left) >= 0 {
        return t.rightRotate(node)
    }

    if balance > 1 && t.getBalance(node.Left) < 0 {
        node.Left = t.leftRotate(node.Left)
        return t.rightRotate(node)
    }

    if balance < -1 && t.getBalance(node.Right) <= 0 {
        return t.leftRotate(node)
    }

    if balance < -1 && t.getBalance(node.Right) > 0 {
        node.Right = t.rightRotate(node.Right)
        return t.leftRotate(node)
    }

    return node
}

func (t *AVLTree) minValueNode(node *TreeNode) *TreeNode {
    current := node
    for current.Left != nil {
        current = current.Left
    }
    return current
}

func (t *AVLTree) searchNode(node *TreeNode, value int) bool {
    if node == nil {
        return false
    }
    if value == node.Value {
        return true
    }
    if value < node.Value {
        return t.searchNode(node.Left, value)
    }
    return t.searchNode(node.Right, value)
}

func (t *AVLTree) inOrderTraversal(node *TreeNode) {
    if node != nil {
        t.inOrderTraversal(node.Left)
        fmt.Printf("%d ", node.Value)
        t.inOrderTraversal(node.Right)
    }
}

func (t *AVLTree) preOrderTraversal(node *TreeNode) {
    if node != nil {
        fmt.Printf("%d ", node.Value)
        t.preOrderTraversal(node.Left)
        t.preOrderTraversal(node.Right)
    }
}

func (t *AVLTree) postOrderTraversal(node *TreeNode) {
    if node != nil {
        t.postOrderTraversal(node.Left)
        t.postOrderTraversal(node.Right)
        fmt.Printf("%d ", node.Value)
    }
}

func (t *AVLTree) countNodes(node *TreeNode) int {
    if node == nil {
        return 0
    }
    return 1 + t.countNodes(node.Left) + t.countNodes(node.Right)
}

func (t *AVLTree) findMin(node *TreeNode) int {
    for node.Left != nil {
        node = node.Left
    }
    return node.Value
}

func (t *AVLTree) findMax(node *TreeNode) int {
    for node.Right != nil {
        node = node.Right
    }
    return node.Value
}

func (t *AVLTree) inOrderCollect(node *TreeNode, result *[]int) {
    if node != nil {
        t.inOrderCollect(node.Left, result)
        *result = append(*result, node.Value)
        t.inOrderCollect(node.Right, result)
    }
}

func (t *AVLTree) preOrderCollect(node *TreeNode, result *[]int) {
    if node != nil {
        *result = append(*result, node.Value)
        t.preOrderCollect(node.Left, result)
        t.preOrderCollect(node.Right, result)
    }
}

func (t *AVLTree) postOrderCollect(node *TreeNode, result *[]int) {
    if node != nil {
        t.postOrderCollect(node.Left, result)
        t.postOrderCollect(node.Right, result)
        *result = append(*result, node.Value)
    }
}

func (t *AVLTree) inOrderSerialize(node *TreeNode, result *[]string) {
    if node != nil {
        t.inOrderSerialize(node.Left, result)
        *result = append(*result, strconv.Itoa(node.Value))
        t.inOrderSerialize(node.Right, result)
    }
}

func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}