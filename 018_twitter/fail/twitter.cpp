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
    std::set<std::string> likes;
public:
    MESSAGE(int id, const std::string& username, const std::string& msg) : id{id}, username{username}, msg{msg} {
    }
    int getId() const {
        return this->id;
    }
    void like(const std::string& username){
        likes.insert(likes.end(), username);
    }
    friend std::ostream& operator<<(std::ostream& os, const MESSAGE& msg){
        os << msg.id << ":" << msg.username << " (" << msg.msg << ") [";
        for (auto like : msg.likes)
            os << like;
        os << "]\n";
        return os;
    }
};

class INBOX {
    std::map<int, MESSAGE*> unread;
    std::map<int, MESSAGE*> allMsgs;
public:
    INBOX(){
    }
    std::vector<MESSAGE*> getUnread(){
        std::vector<MESSAGE*> msg;
        for (auto ms : unread)
            msg.push_back(ms.second);
        unread.clear();
        return msg;
    }
    std::vector<MESSAGE*> getAll() const {
        std::vector<MESSAGE*> msg;
        for (auto ms : allMsgs)
            msg.push_back(ms.second);
        return msg;
    }
    MESSAGE* getTweet(int id){
        return allMsgs[id];
    }
    friend std::ostream& operator<<(std::ostream& os, const INBOX& inbox){
        for (auto msg : inbox.unread)
            os << *msg.second;
        return os;
    }
    void storeUnread(MESSAGE* tweet){
        this->unread[tweet->getId()] = tweet;
        this->storeReaded(tweet);
    }
    void storeReaded(MESSAGE* tweet){
        this->allMsgs[tweet->getId()] = tweet;
    }
};

class USER {
    std::string username;
    INBOX inbox;
    std::map<std::string, USER*> followers;
    std::map<std::string, USER*> following;
public:
    void send(MESSAGE* msg){
        this->inbox.storeUnread(msg);
    }
    USER(const std::string& username) : username(username) {
    }
    void follow(USER* other){
        this->following[other->username] = other;
        other->followers[this->username] = this;
    }
    void unfollow(std::string username){
        auto user = this->following.find(username);
        if (user == following.end())
            return;
        following.erase(user);
        user->second->followers.erase(this->username);
    }
    void like(int twId){
        std::vector<MESSAGE*> us = this->inbox.getAll();
        us[twId]->like(this->username);
    }
    INBOX& getInbox(){
        return this->inbox;
    }
    friend std::ostream& operator<<(std::ostream& os, const USER& user){
        os << user.username << "\n\tseguidos [ ";
        for (auto fol : user.following)
            os << fol.second->username << " ";
        os << "]\n\tseguidores [ ";

        for (auto seg : user.followers)
            os << seg.second->username << " ";
        os << "]";

        return os;
    }
};

class SYSTEM {
    std::map<std::string, std::shared_ptr<USER>> users;
    std::map<int, std::shared_ptr<MESSAGE>> tweets;
    int nextTweetId { 0 };
    //create, stores and returns a new tweet object
    MESSAGE* createMsg(std::string username, std::string msg){
        tweets[nextTweetId] = std::make_shared<MESSAGE>(nextTweetId, username, msg);
        nextTweetId++;
        return tweets[nextTweetId--].get();
    }
public:
    SYSTEM(){
    }
    void addUser(std::string username){
        users[username] = std::make_shared<USER>(username);
    }
    USER* getUser(std::string username){
        auto user = users.find(username);
        return user->second.get();
    }
    void sendTweet(std::string username, std::string msg){
        USER* user = this->getUser(username);
        this->tweets[nextTweetId] = std::make_shared<MESSAGE>(createMsg(username, msg));
    }
    friend std::ostream& operator<<(std::ostream& os, const SYSTEM& system);
};
std::ostream& operator<<(std::ostream& os, const SYSTEM& system){
    for (auto user : system.users)
        os << *user.second << "\n";
    return os;
}

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
                control.getUser(seguir)->follow(control.getUser(seguido));
            }
            else if (cmd == "twittar") {
                std::string userName;
                std::string msg;
                ss >> userName;
                getline(ss, msg);
                control.sendTweet(userName, msg.substr(1));
            }
            else if (cmd == "timeline") {
                std::string userName;
                ss >> userName;
                control.getUser(userName)->getInbox();
            }
            else if (cmd == "like") {
                std::string userName;
                int id;
                ss >> userName >> id;
                control.getUser(userName)->like(id);
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