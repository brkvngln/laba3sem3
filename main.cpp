#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <functional>
#include <sstream>
#include "common_types.h"
#include "mfuncs.h"
#include "ffuncs.h"
#include "lfuncs.h"
#include "qfuncs.h"
#include "sfuncs.h"
#include "tfuncs.h"
#include "hfuncs.h"

DynamicArray* m_arr = nullptr;
ForwardList* f_list = nullptr;
DoublyLinkedList* l_list = nullptr;
Queue* q_queue = nullptr;
Stack* s_stack = nullptr;
AVLTree* t_tree = nullptr;
HashTable* h_table = nullptr;

const std::string TEXT_SUFFIX = ".txt";
const std::string BINARY_SUFFIX = ".bin";

std::string M_FILE = "array_data.txt";
std::string F_FILE = "flist_data.txt";
std::string L_FILE = "llist_data.txt";
std::string Q_FILE = "queue_data.txt";
std::string S_FILE = "stack_data.txt";
std::string T_FILE = "tree_data.txt";
std::string H_FILE = "hash_data.txt";

void set_filenames(const std::string& base_name, bool binary = false) {
    std::string suffix = binary ? BINARY_SUFFIX : TEXT_SUFFIX;
    M_FILE = base_name + "_array" + suffix;
    F_FILE = base_name + "_flist" + suffix;
    L_FILE = base_name + "_llist" + suffix;
    Q_FILE = base_name + "_queue" + suffix;
    S_FILE = base_name + "_stack" + suffix;
    T_FILE = base_name + "_tree" + suffix;
    H_FILE = base_name + "_hash" + suffix;
}

bool is_binary_format(const std::string& filename) {
    if (filename.length() >= BINARY_SUFFIX.length()) {
        return filename.compare(filename.length() - BINARY_SUFFIX.length(), 
                              BINARY_SUFFIX.length(), BINARY_SUFFIX) == 0;
    }
    return false;
}

void save_structure(const std::string& filename, Serializable* structure, bool binary) {
    if (!structure) return;
    
    if (binary) {
        std::ofstream file(filename, std::ios::binary);
        if (file.is_open()) {
            structure->serializeBinary(file);
            file.close();
        }
    } else {
        std::vector<std::string> data = structure->serialize();
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& item : data) {
                file << item << std::endl;
            }
            file.close();
        }
    }
}

void load_structure(const std::string& filename, Serializable* structure, bool binary) {
    if (!structure) return;
    
    if (binary) {
        std::ifstream file(filename, std::ios::binary);
        if (file.is_open()) {
            structure->deserializeBinary(file);
            file.close();
        }
    } else {
        std::vector<std::string> data;
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (!line.empty()) {
                    data.push_back(line);
                }
            }
            file.close();
        }
        if (!data.empty()) {
            structure->deserialize(data);
        }
    }
}

void save_all_structures(bool binary = false) {
    if (m_arr) save_structure(M_FILE, m_arr, binary);
    if (f_list) save_structure(F_FILE, f_list, binary);
    if (l_list) save_structure(L_FILE, l_list, binary);
    if (q_queue) save_structure(Q_FILE, q_queue, binary);
    if (s_stack) save_structure(S_FILE, s_stack, binary);
    if (t_tree) save_structure(T_FILE, t_tree, binary);
    if (h_table) save_structure(H_FILE, h_table, binary);
    
    std::cout << "OK: Data saved in " << (binary ? "binary" : "text") << " format" << std::endl;
}

void load_all_structures(bool binary = false) {
    if (!m_arr) m_arr = new DynamicArray();
    load_structure(M_FILE, m_arr, binary);
    
    if (!f_list) f_list = new ForwardList();
    load_structure(F_FILE, f_list, binary);
    
    if (!l_list) l_list = new DoublyLinkedList();
    load_structure(L_FILE, l_list, binary);
    
    if (!q_queue) q_queue = new Queue();
    load_structure(Q_FILE, q_queue, binary);
    
    if (!s_stack) s_stack = new Stack();
    load_structure(S_FILE, s_stack, binary);
    
    if (!t_tree) t_tree = new AVLTree();
    load_structure(T_FILE, t_tree, binary);
    
    if (!h_table) h_table = new HashTable();
    load_structure(H_FILE, h_table, binary);
    
    std::cout << "OK: Data loaded from " << (binary ? "binary" : "text") << " format" << std::endl;
}

void MPUSHFRONT(const std::string& value) {
    if (!m_arr) m_arr = new DynamicArray();
    m_arr->insert(0, value);
    std::cout << "OK" << std::endl;
}

void MPUSHBACK(const std::string& value) {
    if (!m_arr) m_arr = new DynamicArray();
    m_arr->pushBack(value);
    std::cout << "OK" << std::endl;
}

void MINSERT(int index, const std::string& value) {
    if (m_arr && index >= 0 && index <= m_arr->getSize()) {
        m_arr->insert(index, value);
        std::cout << "OK" << std::endl;
    }
    else {
        std::cout << "ERROR: Invalid index" << std::endl;
    }
}

void MDEL(int index) {
    if (m_arr && index >= 0 && index < m_arr->getSize()) {
        std::string value = m_arr->get(index);
        m_arr->remove(index);
        std::cout << "OK: " << value << std::endl;
    }
    else {
        std::cout << "ERROR: Invalid index" << std::endl;
    }
}

void MSET(int index, const std::string& value) {
    if (m_arr && index >= 0 && index < m_arr->getSize()) {
        m_arr->set(index, value);
        std::cout << "OK" << std::endl;
    }
    else {
        std::cout << "ERROR: Invalid index" << std::endl;
    }
}

void MGET(int index) {
    if (m_arr && index >= 0 && index < m_arr->getSize()) {
        std::cout << m_arr->get(index) << std::endl;
    }
    else {
        std::cout << "ERROR: Invalid index" << std::endl;
    }
}

void MFIND(const std::string& value) {
    if (m_arr) {
        int index = m_arr->find(value);
        if (index != -1) {
            std::cout << index << std::endl;
        }
        else {
            std::cout << "NOT_FOUND" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: Array is empty" << std::endl;
    }
}

void MPRINT() {
    if (m_arr) m_arr->print();
    else std::cout << "EMPTY" << std::endl;
}

void MSIZE() {
    if (m_arr) {
        std::cout << "Size: " << m_arr->getSize() << ", Capacity: " << m_arr->getCapacity() << std::endl;
    }
    else {
        std::cout << "Size: 0, Capacity: 0" << std::endl;
    }
}

void MCLEAR() {
    if (m_arr) {
        m_arr->clear();
    }
    std::cout << "OK" << std::endl;
}

void FPUSHFRONT(const std::string& value) {
    if (!f_list) f_list = new ForwardList();
    f_list->pushFront(value);
    std::cout << "OK" << std::endl;
}

void FPUSHBACK(const std::string& value) {
    if (!f_list) f_list = new ForwardList();
    f_list->pushBack(value);
    std::cout << "OK" << std::endl;
}

void FADDAFTER(const std::string& after_value, const std::string& value) {
    FNode* found = f_list->find(after_value);
    if (found) {
        f_list->addAfter(found, value);
        std::cout << "OK" << std::endl;
    }
    else {
        std::cout << "ERROR: Element not found" << std::endl;
    }
}

void FDELAFTER(const std::string& after_value) {
    FNode* found = f_list->find(after_value);
    if (found && found->next != nullptr) {
        f_list->delAfter(found);
        std::cout << "OK" << std::endl;
    }
    else {
        std::cout << "ERROR: Cannot delete" << std::endl;
    }
}

void FADDBEFORE(const std::string& before_value, const std::string& value) {
    if (f_list) {
        FNode* found = f_list->find(before_value);
        if (found) {
            f_list->addBefore(found, value);
            std::cout << "OK" << std::endl;
        }
        else {
            std::cout << "ERROR: Element not found" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void FDELBEFORE(const std::string& before_value) {
    if (f_list) {
        FNode* found = f_list->find(before_value);
        if (found) {
            f_list->delBefore(found);
            std::cout << "OK" << std::endl;
        }
        else {
            std::cout << "ERROR: Element not found" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void FPOPFRONT() {
    if (f_list) {
        f_list->popFront();
        std::cout << "OK" << std::endl;
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void FDEL(const std::string& value) {
    if (f_list) {
        FNode* found = f_list->find(value);
        if (found) {
            f_list->delByKey(value);
            std::cout << "OK" << std::endl;
        }
        else {
            std::cout << "ERROR: Element not found" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void FGET(int index) {
    if (f_list) {
        std::string value = f_list->getAt(index);
        if (!value.empty()) {
            std::cout << value << std::endl;
        }
        else {
            std::cout << "ERROR: Invalid index" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void FFIND(const std::string& value) {
    if (f_list) {
        FNode* found = f_list->find(value);
        if (found) {
            std::cout << "FOUND" << std::endl;
        }
        else {
            std::cout << "NOT_FOUND" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void FPRINT() {
    if (f_list) f_list->print();
    else std::cout << "EMPTY" << std::endl;
}

void FSIZE() {
    if (f_list) {
        std::cout << f_list->getSize() << std::endl;
    }
    else {
        std::cout << "0" << std::endl;
    }
}

void FCLEAR() {
    if (f_list) {
        delete f_list;
        f_list = nullptr;
    }
    std::cout << "OK" << std::endl;
}

void LPUSHFRONT(const std::string& value) {
    if (!l_list) l_list = new DoublyLinkedList();
    l_list->pushFront(value);
    std::cout << "OK" << std::endl;
}

void LPUSHBACK(const std::string& value) {
    if (!l_list) l_list = new DoublyLinkedList();
    l_list->pushBack(value);
    std::cout << "OK" << std::endl;
}

void LADDAFTER(const std::string& after_value, const std::string& value) {
    if (l_list) {
        LNode* found = l_list->find(after_value);
        if (found) {
            l_list->addAfter(found, value);
            std::cout << "OK" << std::endl;
        }
        else {
            std::cout << "ERROR: Element not found" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void LADDBEFORE(const std::string& before_value, const std::string& value) {
    if (l_list) {
        LNode* found = l_list->find(before_value);
        if (found) {
            l_list->addBefore(found, value);
            std::cout << "OK" << std::endl;
        }
        else {
            std::cout << "ERROR: Element not found" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void LPOPFRONT() {
    if (l_list) {
        l_list->popFront();
        std::cout << "OK" << std::endl;
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void LPOPBACK() {
    if (l_list) {
        l_list->popBack();
        std::cout << "OK" << std::endl;
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void LDELAFTER(const std::string& after_value) {
    if (l_list) {
        LNode* found = l_list->find(after_value);
        if (found && found->next != nullptr) {
            l_list->delAfter(found);
            std::cout << "OK" << std::endl;
        }
        else {
            std::cout << "ERROR: Cannot delete" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void LDELBEFORE(const std::string& before_value) {
    if (l_list) {
        LNode* found = l_list->find(before_value);
        if (found && found->prev != nullptr) {
            l_list->delBefore(found);
            std::cout << "OK" << std::endl;
        }
        else {
            std::cout << "ERROR: Cannot delete" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void LDEL(const std::string& value) {
    if (l_list) {
        LNode* found = l_list->find(value);
        if (found) {
            l_list->delByKey(value);
            std::cout << "OK" << std::endl;
        }
        else {
            std::cout << "ERROR: Element not found" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void LGET(int index) {
    if (l_list) {
        std::string value = l_list->getAt(index);
        if (!value.empty()) {
            std::cout << value << std::endl;
        }
        else {
            std::cout << "ERROR: Invalid index" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void LFIND(const std::string& value) {
    if (l_list) {
        LNode* found = l_list->find(value);
        if (found) {
            std::cout << "FOUND" << std::endl;
        }
        else {
            std::cout << "NOT_FOUND" << std::endl;
        }
    }
    else {
        std::cout << "ERROR: List is empty" << std::endl;
    }
}

void LPRINT() {
    if (l_list) l_list->print();
    else std::cout << "EMPTY" << std::endl;
}

void LPRINTREVERSE() {
    if (l_list) l_list->printReverse();
    else std::cout << "EMPTY" << std::endl;
}

void LSIZE() {
    if (l_list) {
        std::cout << l_list->getSize() << std::endl;
    }
    else {
        std::cout << "0" << std::endl;
    }
}

void LCLEAR() {
    if (l_list) {
        delete l_list;
        l_list = nullptr;
    }
    std::cout << "OK" << std::endl;
}

void QPUSH(const std::string& value) {
    if (!q_queue) q_queue = new Queue();
    q_queue->push(value);
    std::cout << "OK" << std::endl;
}

void QPOP() {
    if (q_queue && !q_queue->empty()) {
        std::string value = q_queue->pop();
        std::cout << value << std::endl;
    }
    else {
        std::cout << "ERROR: Queue is empty" << std::endl;
    }
}

void QFRONT() {
    if (q_queue && !q_queue->empty()) {
        std::cout << q_queue->getFront() << std::endl;
    }
    else {
        std::cout << "ERROR: Queue is empty" << std::endl;
    }
}

void QREAR() {
    if (q_queue && !q_queue->empty()) {
        std::cout << q_queue->getRear() << std::endl;
    }
    else {
        std::cout << "ERROR: Queue is empty" << std::endl;
    }
}

void QPRINT() {
    if (q_queue) q_queue->print();
    else std::cout << "EMPTY" << std::endl;
}

void QSIZE() {
    if (q_queue) {
        std::cout << q_queue->size() << std::endl;
    }
    else {
        std::cout << "0" << std::endl;
    }
}

void QCLEAR() {
    if (q_queue) {
        q_queue->clear();
    }
    std::cout << "OK" << std::endl;
}

void SPUSH(const std::string& value) {
    if (!s_stack) s_stack = new Stack();
    s_stack->push(value);
    std::cout << "OK" << std::endl;
}

void SPOP() {
    if (s_stack && !s_stack->empty()) {
        std::string value = s_stack->pop();
        std::cout << value << std::endl;
    }
    else {
        std::cout << "ERROR: Stack is empty" << std::endl;
    }
}

void STOP() {
    if (s_stack && !s_stack->empty()) {
        std::cout << s_stack->getTop() << std::endl;
    }
    else {
        std::cout << "ERROR: Stack is empty" << std::endl;
    }
}

void SPRINT() {
    if (s_stack) s_stack->print();
    else std::cout << "EMPTY" << std::endl;
}

void SSIZE() {
    if (s_stack) {
        std::cout << s_stack->size() << std::endl;
    }
    else {
        std::cout << "0" << std::endl;
    }
}

void SCLEAR() {
    if (s_stack) {
        s_stack->clear();
    }
    std::cout << "OK" << std::endl;
}

void TINSERT(int value) {
    if (!t_tree) t_tree = new AVLTree();
    t_tree->insert(value);
    std::cout << "OK" << std::endl;
}

void TDEL(int value) {
    if (t_tree && t_tree->search(value)) {
        t_tree->remove(value);
        std::cout << "OK" << std::endl;
    }
    else {
        std::cout << "ERROR: Element not found" << std::endl;
    }
}

void TSEARCH(int value) {
    if (t_tree && t_tree->search(value)) {
        std::cout << "FOUND" << std::endl;
    }
    else {
        std::cout << "NOT_FOUND" << std::endl;
    }
}

void TPRINTINORDER() {
    if (t_tree) t_tree->printInOrder();
    else std::cout << "EMPTY" << std::endl;
}

void TPRINTPREORDER() {
    if (t_tree) t_tree->printPreOrder();
    else std::cout << "EMPTY" << std::endl;
}

void TPRINTPOSTORDER() {
    if (t_tree) t_tree->printPostOrder();
    else std::cout << "EMPTY" << std::endl;
}

void TMIN() {
    if (t_tree && !t_tree->empty()) {
        int min_val = t_tree->Min();
        if (min_val != -1) {
            std::cout << min_val << std::endl;
        }
        else {
            std::cout << "EMPTY" << std::endl;
        }
    }
    else {
        std::cout << "EMPTY" << std::endl;
    }
}

void TMAX() {
    if (t_tree && !t_tree->empty()) {
        int max_val = t_tree->Max();
        if (max_val != -1) {
            std::cout << max_val << std::endl;
        }
        else {
            std::cout << "EMPTY" << std::endl;
        }
    }
    else {
        std::cout << "EMPTY" << std::endl;
    }
}

void TSIZE() {
    if (t_tree) {
        std::cout << t_tree->size() << std::endl;
    }
    else {
        std::cout << "0" << std::endl;
    }
}

void THEIGHT() {
    if (t_tree) {
        std::cout << t_tree->height() << std::endl;
    }
    else {
        std::cout << "0" << std::endl;
    }
}

void TCLEAR() {
    if (t_tree) {
        delete t_tree;
        t_tree = nullptr;
    }
    std::cout << "OK" << std::endl;
}

void HINSERT(const std::string& key, const std::string& value) {
    if (!h_table) h_table = new HashTable();
    if (h_table->insert(key, value)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "ERROR: Insert failed" << std::endl;
    }
}

void HFIND(const std::string& key) {
    if (h_table) {
        std::string value;
        if (h_table->find(key, value)) {
            std::cout << key << ":" << value << std::endl;
        } else {
            std::cout << "NOT_FOUND" << std::endl;
        }
    } else {
        std::cout << "EMPTY" << std::endl;
    }
}

void HREMOVE(const std::string& key) {
    if (h_table && h_table->remove(key)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "ERROR: Key not found" << std::endl;
    }
}

void HPRINT() {
    if (h_table) h_table->print();
    else std::cout << "EMPTY" << std::endl;
}

void HSIZE() {
    if (h_table) {
        std::cout << "Size: " << h_table->getSize() << ", Capacity: " << h_table->getCapacity() << std::endl;
    } else {
        std::cout << "Size: 0, Capacity: 0" << std::endl;
    }
}

void HCLEAR() {
    if (h_table) {
        h_table->clear();
    }
    std::cout << "OK" << std::endl;
}

void PRINT() {
    std::cout << "\n=== ALL STRUCTURES ===" << std::endl;
    MPRINT();
    FPRINT();
    LPRINT();
    QPRINT();
    SPRINT();
    TPRINTINORDER();
    HPRINT();
}

void SAVE() {
    save_all_structures(false);
}

void SAVE_BINARY() {
    save_all_structures(true);
}

void LOAD() {
    load_all_structures(false);
}

void LOAD_BINARY() {
    load_all_structures(true);
}

void HELP() {
    std::cout << "=== AVAILABLE COMMANDS ===" << std::endl;
    std::cout << "Array (M): MPUSHFRONT <value>, MPUSHBACK <value>, MINSERT <index> <value>" << std::endl;
    std::cout << "          MDEL <index>, MSET <index> <value>, MGET <index>, MFIND <value>" << std::endl;
    std::cout << "          MPRINT, MSIZE, MCLEAR" << std::endl;
    
    std::cout << "Forward List (F): FPUSHFRONT <value>, FPUSHBACK <value>, FADDAFTER <after> <value>" << std::endl;
    std::cout << "                 FDELAFTER <after>, FADDBEFORE <before> <value>, FDELBEFORE <before>" << std::endl;
    std::cout << "                 FPOPFRONT, FDEL <value>, FGET <index>, FFIND <value>" << std::endl;
    std::cout << "                 FPRINT, FSIZE, FCLEAR" << std::endl;
    
    std::cout << "Doubly List (L): LPUSHFRONT <value>, LPUSHBACK <value>, LADDAFTER <after> <value>" << std::endl;
    std::cout << "                LADDBEFORE <before> <value>, LPOPFRONT, LPOPBACK, LDELAFTER <after>" << std::endl;
    std::cout << "                LDELBEFORE <before>, LDEL <value>, LGET <index>, LFIND <value>" << std::endl;
    std::cout << "                LPRINT, LPRINTREVERSE, LSIZE, LCLEAR" << std::endl;
    
    std::cout << "Queue (Q): QPUSH <value>, QPOP, QFRONT, QREAR, QPRINT, QSIZE, QCLEAR" << std::endl;
    std::cout << "Stack (S): SPUSH <value>, SPOP, STOP, SPRINT, SSIZE, SCLEAR" << std::endl;
    
    std::cout << "Tree (T): TINSERT <value>, TDEL <value>, TSEARCH <value>, TPRINTINORDER" << std::endl;
    std::cout << "         TPRINTPREORDER, TPRINTPOSTORDER, TMIN, TMAX, TSIZE, THEIGHT, TCLEAR" << std::endl;
    
    std::cout << "Hash (H): HINSERT <key> <value>, HFIND <key>, HREMOVE <key>" << std::endl;
    std::cout << "         HPRINT, HSIZE, HCLEAR" << std::endl;
    
    std::cout << "System: PRINT, SAVE, LOAD, SAVE_BINARY, LOAD_BINARY, HELP, EXIT" << std::endl;
}

bool process_command(const std::string& command_line) {
    std::istringstream iss(command_line);
    std::string command;
    iss >> command;
    
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);
    
    if (command == "EXIT") {
        return false;
    }
    else if (command == "HELP") {
        HELP();
    }
    else if (command == "PRINT") {
        PRINT();
    }
    else if (command == "SAVE") {
        SAVE();
    }
    else if (command == "SAVE_BINARY") {
        SAVE_BINARY();
    }
    else if (command == "LOAD") {
        LOAD();
    }
    else if (command == "LOAD_BINARY") {
        LOAD_BINARY();
    }
    else if (command == "MPUSHFRONT") {
        std::string value;
        if (iss >> value) MPUSHFRONT(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "MPUSHBACK") {
        std::string value;
        if (iss >> value) MPUSHBACK(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "MINSERT") {
        int index;
        std::string value;
        if (iss >> index >> value) MINSERT(index, value);
        else std::cout << "ERROR: Missing index or value" << std::endl;
    }
    else if (command == "MDEL") {
        int index;
        if (iss >> index) MDEL(index);
        else std::cout << "ERROR: Missing index" << std::endl;
    }
    else if (command == "MSET") {
        int index;
        std::string value;
        if (iss >> index >> value) MSET(index, value);
        else std::cout << "ERROR: Missing index or value" << std::endl;
    }
    else if (command == "MGET") {
        int index;
        if (iss >> index) MGET(index);
        else std::cout << "ERROR: Missing index" << std::endl;
    }
    else if (command == "MFIND") {
        std::string value;
        if (iss >> value) MFIND(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "MPRINT") {
        MPRINT();
    }
    else if (command == "MSIZE") {
        MSIZE();
    }
    else if (command == "MCLEAR") {
        MCLEAR();
    }
    else if (command == "FPUSHFRONT") {
        std::string value;
        if (iss >> value) FPUSHFRONT(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "FPUSHBACK") {
        std::string value;
        if (iss >> value) FPUSHBACK(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "FADDAFTER") {
        std::string after, value;
        if (iss >> after >> value) FADDAFTER(after, value);
        else std::cout << "ERROR: Missing parameters" << std::endl;
    }
    else if (command == "FDELAFTER") {
        std::string after;
        if (iss >> after) FDELAFTER(after);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "FADDBEFORE") {
        std::string before, value;
        if (iss >> before >> value) FADDBEFORE(before, value);
        else std::cout << "ERROR: Missing parameters" << std::endl;
    }
    else if (command == "FDELBEFORE") {
        std::string before;
        if (iss >> before) FDELBEFORE(before);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "FPOPFRONT") {
        FPOPFRONT();
    }
    else if (command == "FDEL") {
        std::string value;
        if (iss >> value) FDEL(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "FGET") {
        int index;
        if (iss >> index) FGET(index);
        else std::cout << "ERROR: Missing index" << std::endl;
    }
    else if (command == "FFIND") {
        std::string value;
        if (iss >> value) FFIND(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "FPRINT") {
        FPRINT();
    }
    else if (command == "FSIZE") {
        FSIZE();
    }
    else if (command == "FCLEAR") {
        FCLEAR();
    }
    else if (command == "LPUSHFRONT") {
        std::string value;
        if (iss >> value) LPUSHFRONT(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "LPUSHBACK") {
        std::string value;
        if (iss >> value) LPUSHBACK(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "LADDAFTER") {
        std::string after, value;
        if (iss >> after >> value) LADDAFTER(after, value);
        else std::cout << "ERROR: Missing parameters" << std::endl;
    }
    else if (command == "LADDBEFORE") {
        std::string before, value;
        if (iss >> before >> value) LADDBEFORE(before, value);
        else std::cout << "ERROR: Missing parameters" << std::endl;
    }
    else if (command == "LPOPFRONT") {
        LPOPFRONT();
    }
    else if (command == "LPOPBACK") {
        LPOPBACK();
    }
    else if (command == "LDELAFTER") {
        std::string after;
        if (iss >> after) LDELAFTER(after);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "LDELBEFORE") {
        std::string before;
        if (iss >> before) LDELBEFORE(before);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "LDEL") {
        std::string value;
        if (iss >> value) LDEL(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "LGET") {
        int index;
        if (iss >> index) LGET(index);
        else std::cout << "ERROR: Missing index" << std::endl;
    }
    else if (command == "LFIND") {
        std::string value;
        if (iss >> value) LFIND(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "LPRINT") {
        LPRINT();
    }
    else if (command == "LPRINTREVERSE") {
        LPRINTREVERSE();
    }
    else if (command == "LSIZE") {
        LSIZE();
    }
    else if (command == "LCLEAR") {
        LCLEAR();
    }
    else if (command == "QPUSH") {
        std::string value;
        if (iss >> value) QPUSH(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "QPOP") {
        QPOP();
    }
    else if (command == "QFRONT") {
        QFRONT();
    }
    else if (command == "QREAR") {
        QREAR();
    }
    else if (command == "QPRINT") {
        QPRINT();
    }
    else if (command == "QSIZE") {
        QSIZE();
    }
    else if (command == "QCLEAR") {
        QCLEAR();
    }
    else if (command == "SPUSH") {
        std::string value;
        if (iss >> value) SPUSH(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "SPOP") {
        SPOP();
    }
    else if (command == "STOP") {
        STOP();
    }
    else if (command == "SPRINT") {
        SPRINT();
    }
    else if (command == "SSIZE") {
        SSIZE();
    }
    else if (command == "SCLEAR") {
        SCLEAR();
    }
    else if (command == "TINSERT") {
        int value;
        if (iss >> value) TINSERT(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "TDEL") {
        int value;
        if (iss >> value) TDEL(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "TSEARCH") {
        int value;
        if (iss >> value) TSEARCH(value);
        else std::cout << "ERROR: Missing value" << std::endl;
    }
    else if (command == "TPRINTINORDER") {
        TPRINTINORDER();
    }
    else if (command == "TPRINTPREORDER") {
        TPRINTPREORDER();
    }
    else if (command == "TPRINTPOSTORDER") {
        TPRINTPOSTORDER();
    }
    else if (command == "TMIN") {
        TMIN();
    }
    else if (command == "TMAX") {
        TMAX();
    }
    else if (command == "TSIZE") {
        TSIZE();
    }
    else if (command == "THEIGHT") {
        THEIGHT();
    }
    else if (command == "TCLEAR") {
        TCLEAR();
    }
    else if (command == "HINSERT") {
        std::string key, value;
        if (iss >> key >> value) HINSERT(key, value);
        else std::cout << "ERROR: Missing key or value" << std::endl;
    }
    else if (command == "HFIND") {
        std::string key;
        if (iss >> key) HFIND(key);
        else std::cout << "ERROR: Missing key" << std::endl;
    }
    else if (command == "HREMOVE") {
        std::string key;
        if (iss >> key) HREMOVE(key);
        else std::cout << "ERROR: Missing key" << std::endl;
    }
    else if (command == "HPRINT") {
        HPRINT();
    }
    else if (command == "HSIZE") {
        HSIZE();
    }
    else if (command == "HCLEAR") {
        HCLEAR();
    }
    else {
        std::cout << "ERROR: Unknown command: " << command << std::endl;
        std::cout << "Use HELP for available commands" << std::endl;
    }
    
    return true;
}

int main(int argc, char* argv[]) {
    bool binary_mode = false;
    std::string filename;
    std::string query;
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else if (arg == "--binary") {
            binary_mode = true;
        } else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        } else if (arg == "HELP" || arg == "help") {
            HELP();
            return 0;
        }
    }
    
    if (!filename.empty()) {
        set_filenames(filename, binary_mode);
        load_all_structures(binary_mode);
        std::cout << "Data loaded from: " << filename << std::endl;
    }
    
    if (!query.empty()) {
        process_command(query);
        save_all_structures(binary_mode);
        return 0;
    }
    
    if (!filename.empty() && query.empty()) {
        std::cout << "Use --query to execute commands" << std::endl;
        return 0;
    }
    
    if (argc == 1) {
        load_all_structures(false);
        
        std::cout << "Database Management System" << std::endl;
        std::cout << "Type HELP for commands, EXIT to quit" << std::endl;
        
        std::string command_line;
        while (true) {
            std::cout << "> ";
            std::getline(std::cin, command_line);
            
            if (command_line.empty()) continue;
            
            if (!process_command(command_line)) {
                break;
            }
        }
    }
    
    save_all_structures(false);
    
    if (m_arr) delete m_arr;
    if (f_list) delete f_list;
    if (l_list) delete l_list;
    if (q_queue) delete q_queue;
    if (s_stack) delete s_stack;
    if (t_tree) delete t_tree;
    if (h_table) delete h_table;
    
    return 0;
}