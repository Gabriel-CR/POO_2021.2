#include <iostream>
#include <set>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

class MESSAGE {
    int id;
    std::string username;
    std::string msg;
    std::set<std::string> likes; //Using a Set would eliminate duplicates

public:
    int getId(){
        return this->id;
    }
    //Initialize all attributes
    MESSAGE(int id, std::string username, std::string msg) : id{id}, username{username}, msg{msg} {
    }
    //add username to likes collection
    void like(std::string username){
        likes.insert(username);
    }
    //mount output string
    std::string toString(){
        std::string os {this->username + " (" + msg + ") ["};
        for (auto like : likes)
            os += like;
        os += "]\n";
        return os;
    }
};

class INBOX {
    std::map<int, MESSAGE*> unread;  //store unread tweets
    std::map<int, MESSAGE*> allMsgs; //store read tweets

public:
    INBOX(){
    }
    //stores message both in unread as in allMsgs
    void receiveNew(MESSAGE* tweet){
        this->allMsgs[tweet->getId()] = tweet;
        this->unread[tweet->getId()] = tweet;
    }
    //stores message as a readed Message
    void store(MESSAGE* tweet){
        this->allMsgs.insert(std::pair<int, MESSAGE*>(allMsgs.size(), tweet));
    }
    //return unread and clean unread Msgs
    std::map<int, MESSAGE*> getUnread(){
        std::map<int, MESSAGE*> un = this->unread;
        unread.clear();
        return un;
    }
    //return all messages
    std::map<int, MESSAGE*> getAll(){
        return this->allMsgs;
    }
    //search for a tweet with this id and return it or throw a MessageException
    MESSAGE getTweet(int id){
        auto it = allMsgs.find(id);
        if (it == allMsgs.end())
            throw std::runtime_error("fail: mensagem nao encontrada");
        else
            return *it->second;
    }
    // return unread
    std::string toString(){
        std::string os;
        for (auto msg : this->getUnread())
            os += std::to_string(msg.first) + ":" + msg.second->toString();
        return os;
    }
};

class USER {
    std::string username;
    std::map<std::string, USER*> followers; //os meus seguidores
    std::map<std::string, USER*> following; //aqueles que eu sigo
    INBOX inbox;

public:
    // Initialize all attributes
    USER(std::string id) : username{id}{
    }
    //if it's still not following
    void follow(USER* other){
        this->following[other->username] = other;  //add other to this.following
        other->followers[this->username] = this;   //add this to other.followers  
    }
    //get the User other from following using username parameter
    void unfollow(std::string username){
        auto user = this->following.find(username);
        if (user == following.end())                    //if other is null then return
            return;
        following.erase(user);                          //remove other from following
        user->second->followers.erase(this->username);   //remove this from other.followers
    }
    //retrieve the tweet from inbox and uses method like
    void like(int twId){
        std::map<int, MESSAGE*> msg = inbox.getAll();
        auto it = this->inbox.getAll().find(twId);
        if (it != msg.end())
            it->second->like(this->username);
        msg.clear();
    }
    //return inbox object
    INBOX getInbox(){
        return this->inbox;
    }
    //Store the message in the user's inbox
    //Put the message as an unread message in each of the follower's inbox
    void sendTweet(MESSAGE* tw){
        this->inbox.receiveNew(tw);
    }
    //show all followers and following by name
    std::string toString(){
        std::string os {this->username + "\n\tseguidos [ "};
        for (auto fol : this->following)
            os += fol.second->username + " ";
            
        os += "]\n\tseguidores [ ";
        for (auto seg : this->followers)
            os += seg.second->username + " ";
        os += "]";
        return os;
    }

    std::string getPosts(){
        std::string msg;
        for (auto follow : this->following) {
            msg += follow.second->getInbox().toString();
        }
        return msg;
    }
};

class SYSTEM {
    std::map<std::string, USER*> users;
    std::map<int, MESSAGE*> messages;
    int twId {0};

public:
    // addUser
    void addUser(std::string nome){
        auto it = users.find(nome);
        if (it != users.end())
            throw std::runtime_error("fail: nome de usuario ja usado");
        else
            users[nome] = new USER(nome);
    }
    // show
    friend std::ostream& operator<<(std::ostream& os, const SYSTEM& system){
        for (auto user : system.users)
            os << user.second->toString() << "\n";
        return os;
    }
    // follow
    void follow(std::string seguir, std::string seguido){
        auto sr = users.find(seguir);
        if (sr == users.end())
            throw std::runtime_error("fail: nome de usuario nao encontrado");
        else {
            auto sg = users.find(seguido);
            sr->second->follow(sg->second);
        }
    }
    // twittar
    void twittar(std::string user, std::string msg){
        auto us = users.find(user);
        if (us == users.end())
            throw std::runtime_error("fail: nome de usuario nao encontrado");
        else {
            us->second->sendTweet(new MESSAGE(twId, user, msg));
            twId++;
        }
    }
    // timeline
    void timeline(std::string user){
        auto us = users.find(user);
        if (us == users.end())
            throw std::runtime_error("fail: nome de usuario nao encontrado");
        else {
            std::cout << us->second->getPosts();
        }
    }
    // like
    void like(std::string user, int id){
        auto msg = this->messages.find(id);
        if (msg == messages.end())
            throw std::runtime_error("fail: menssagem nao encontrada");
        else
            msg->second->like(user);
        messages[id]->like(user);
    }
    // unfollow
};

int main(){
    SYSTEM control;

    std::cout << "SEU SISTEMA ESTA PRONTO" << std::endl;
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        try {
            if (cmd == "end") {
                break;
            }
            else if (cmd == "show") {
                std::cout << control;
            }
            else if (cmd == "addUser") {
                std::string nome;
                ss >> nome;
                control.addUser(nome);
            }
            else if (cmd == "follow") {
                std::string seguir;
                std::string seguido;
                ss >> seguir >> seguido;
                control.follow(seguir, seguido);
            }
            else if (cmd == "twittar") {
                std::string userName;
                std::string msg;
                ss >> userName;
                getline(ss, msg);
                control.twittar(userName, msg.substr(1));
            }
            else if (cmd == "timeline") {
                std::string userName;
                ss >> userName;
                control.timeline(userName);
            }
            else if (cmd == "like") {
                std::string userName;
                int id;
                ss >> userName >> id;
                control.like(userName, id);
            }
            else {
                std::cout << "fail: comando invalido" << std::endl;
            }
        }
        catch (std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}