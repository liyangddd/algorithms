#include <set>
#include <string>
using namespace std;

//class Message;
//class Folder {
//public:
//	Folder() {}
//
//	//复制构造函数、赋值操作符、析构函数被称为复制控制
//	Folder(const Folder&);
//	Folder& operator= (const Folder&);
//	~Folder();
//
//	void save(Message&);
//	void remove(Message&);
//
//	void addMsg(Message*);
//	void remMsg(Message*);
//
//private:
//	set<Message*> messages;
//	void put_Fldr_in_Messages(const set<Message*>&);
//	void remove_Fldr_from_Messages();
//};
//
//class Message {
//public:
//	Message(const string &str = ""): contents(str) {}
//	
//	//复制构造函数、赋值操作符、析构函数被称为复制控制
//	Message(const Message&);
//	Message& operator=(const Message&);
//	~Message();
//
//	void save(Folder&);
//	void remove(Folder&);
//
//	void addFldr(Folder*);
//	void remFldr(Folder*);
//private:
//	string contents;
//	set<Folder*> folders;
//	void put_Msg_in_Folders(const set<Folder*>&);
//	void remove_Msg_from_Folders();
//};
//
//Folder::Folder(const Folder& f):messages(f.messages) {
//	put_Fldr_in_Messages(messages);
//}
//
//void Folder::put_Fldr_in_Messages(const set<Message*>& rhs) {
//	for (set<Message*>::const_iterator beg = rhs.begin();
//		beg != rhs.end(); ++beg)
//		(*beg)->addFldr(this);
//}
//
////注意处理赋值操作符的自我赋值问题
//Folder& Folder::operator=(const Folder &rhs) {
//	if (&rhs != this) {
//		remove_Fldr_from_Messages();
//		messages = rhs.messages;
//		put_Fldr_in_Messages(rhs.messages);
//	}
//	return *this;
//}
//
//void Folder::remove_Fldr_from_Messages() {
//	for (set<Message*>::const_iterator beg = messages.begin();
//		beg != messages.end(); ++beg)
//		(*beg)->remFldr(this);
//} 
//
//Folder::~Folder() {
//	remove_Fldr_from_Messages();
//}