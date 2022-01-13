#include <iostream>
#include <set>
#include <map>
#include <memory>

class MESSAGE {
    int id;
    std::string username;
    std::string msg;
    std::set<std::string> likes; //Using a Set would eliminate duplicates

public:
    int getId();
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
        os += "]";
        return os;
    }
};

class INBOX {
    std::map<int, MESSAGE> unread; //store unread tweets
    std::map<int, MESSAGE> allMsgs; //store read tweets

public:
    INBOX(){
    }
    //stores message both in unread as in allMsgs
    void receiveNew(MESSAGE tweet){
        unread.insert(std::pair<int, MESSAGE>(unread.size(), tweet));
        allMsgs.insert(std::pair<int, MESSAGE>(allMsgs.size(), tweet));
    }
    //stores message as a readed Message
    void store(MESSAGE tweet){
        allMsgs.insert(std::pair<int, MESSAGE>(allMsgs.size(), tweet));
    }
    //return unread and clean unread Msgs
    std::map<int, MESSAGE> getUnread(){
        std::map<int, MESSAGE> un = this->unread;
        unread.clear();
        return un;
    }
    //return all messages
    std::map<int, MESSAGE> getAll(){
        return this->allMsgs;
    }
    //search for a tweet with this id and return it or throw a MessageException
    MESSAGE getTweet(int id){
        auto it = allMsgs.find(id);
        if (it == allMsgs.end())
            throw std::runtime_error("fail: mensagem nao encontrada");
        else
            return it->second;
    }
    //return allMsgs
    std::string toString(){
        std::string os;
        for (auto msg : this->allMsgs)
            os += std::to_string(msg.first) + ":" + msg.second.toString();
        return os;
    }
};

class USER {
    std::string username;
    std::map<std::string, USER> followers; //os meus seguidores
    std::map<std::string, USER> following; //aqueles que eu sigo
    std::shared_ptr<INBOX> inbox;

public:
    // Initialize all attributes
    USER(std::string id) : username{id}{
    }
    //if it's still not following
    //add other to this.following
    //add this to other.followers
    void follow(USER other);
    //get the User other from following using username parameter
    //if other is null then return
    //remove other from following
    //remove this from other.followers
    void unfollow(std::string username);
    //retrieve the tweet from inbox and uses method like
    void like(int twId);
    //return inbox object
    INBOX getInbox();
    //Store the message in the user's inbox
    //Put the message as an unread message in each of the follower's inbox
    void sendTweet(MESSAGE tw);
    //show all followers and following by name
    std::string toString();
};

int main(){
    MESSAGE ms(1, "gab", "hello, world!");
    INBOX in;

    in.receiveNew(ms);

    std::cout << in.toString() << std::endl;

    return 0;
}