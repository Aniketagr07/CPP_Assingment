#include <iostream>
using namespace std;

struct ListNode{
    int data;
    ListNode *next ;
} ;

ListNode* insertNodeAtStart(ListNode *head, int val){
    ListNode *temp = new ListNode ;
    temp->data = val ;
    temp->next = NULL ;
    temp->next = head ;
    head = temp ;
    return head ;
}

ListNode* insertNodeAtEnd(ListNode *head,int val){
    if(head==NULL){
        head= new ListNode ;
        head->data = val;
        head->next = NULL ;
        return head;
    }
    ListNode *itr = head ;
    while(itr->next!=NULL){
        itr= itr->next ;
    }
    itr->next = new ListNode ;
    itr= itr->next ;
    itr->data= val ;
    itr->next = nullptr ;
    return head ;
}

ListNode* deleteNodeAtEnd(ListNode * head){
    ListNode *itr = head ;
    if(itr==NULL){
        return NULL ;
    }
    if (itr->next==NULL){
        delete itr ;
        head = NULL ;
        return head ;
    }
    while(itr->next->next!=NULL){
        itr= itr->next ;
    }
    ListNode *temp = itr->next ;
    itr->next= NULL ;
    delete temp ;
    temp = NULL ;
    return head ;
}

ListNode* deleteNodeAtStart(ListNode *head){
    ListNode *temp = head ;
    if(head==NULL){
        return head ;
    }
    if(head->next==NULL){
        delete head ;
        head = NULL ;
        return head ;
    }
    head= head->next ;
    delete temp ;
    temp = nullptr ;
    return head ;
}

void displayLinkedList(ListNode *head){
    ListNode *itr = head ;
    while(itr!=NULL){
        cout<<itr->data<<"->" ;
        itr= itr->next ;
    }
    cout<<"nullptr\n" ;
}

int main() 
{
    ListNode *head = NULL ;
    int n ;
    cin>>n ;
    int temp ;
    while(n--){
        cin>>temp ;
        head= insertNodeAtEnd(head, temp) ;
    }
    displayLinkedList(head) ;
    head = deleteNodeAtEnd(head);
    displayLinkedList(head) ;
    head = deleteNodeAtStart(head) ;
    displayLinkedList(head) ;
    cout<<"Insert element-> " ;
    cin>>temp ;
    head = insertNodeAtStart(head, temp) ;
    displayLinkedList(head) ;
    return 0;
}