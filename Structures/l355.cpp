#include <algorithm>
#include <cassert>
#include <map>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

static bool cmp (const pair<int, int> & a, const pair<int, int> & b)
{
    return a.first > b.first;
}

class Twitter {
    struct User {
        int id_;
        vector<int> follow_;
        map<int, int, greater<int>> posts_; // sorted by id_
    };

public:
    Twitter() {}

    void postTweet(int userId, int tweetId) {
        auto p = users_.find(userId);
        if (p == users_.end())
        {
            User new_user;
            new_user.id_ = userId;
            users_.insert({userId, new_user});
            p = users_.find(userId);
        }
        p->second.posts_.insert({id_++, tweetId});
    }

    vector<int> getNewsFeed(int userId) {
        vector<int> res;
        auto p = users_.find(userId);
        if (p == users_.end())
            return res;

        int i = 0;
        vector<pair<int, int>> posts;
        for (auto b = p->second.posts_.begin(); i < 10 && b != p->second.posts_.end(); b++, i++)
            posts.push_back(*b);

        sort(posts.begin(), posts.end(), cmp);
        assert(posts.size() <= 10);
        for (auto x : p->second.follow_)
        {
            auto follow = users_.find(x);
            if (follow == users_.end())
                continue;

            for (auto y : follow->second.posts_)
            {
                if (posts.size() > 0 && y.first > posts.back().first && posts.size() >= 10)
                    posts.pop_back();
                else if (posts.size() >= 10)
                    break;
                if (posts.size() < 10)
                {
                    posts.push_back(y);
                    sort(posts.begin(), posts.end(), cmp);
                }
            }
        }

        for (auto x : posts)
            res.push_back(x.second);
        return res;
    }

    void follow(int followerId, int followeeId) {
        auto p = users_.find(followerId);
        if (p == users_.end())
        {
            User new_user;
            new_user.id_ = followerId;
            users_.insert({followerId, new_user});
            p = users_.find(followerId);
        }
        for (auto x : p->second.follow_)
            if (followeeId == x)
                return;
        p->second.follow_.push_back(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        auto p = users_.find(followerId);
        if (p == users_.end())
            return;
        for (auto x = p->second.follow_.begin(); x != p->second.follow_.end(); x++)
        {
            if (*x == followeeId)
            {
                p->second.follow_.erase(x);
                return;
            }
        }
    }

private:
    unordered_map<int, User> users_; // user_id -> set of tweet ids
    int id_ = 0;
};

int main(int argc, char const *argv[])
{
    Twitter s;
    s.postTweet(1, 5);
    assert(s.getNewsFeed(1) == vector<int>({5}));
    s.follow(1, 2);
    s.postTweet(2, 6);
    assert(s.getNewsFeed(1) == vector<int>({6, 5}));
    s.unfollow(1, 2);
    assert(s.getNewsFeed(1) == vector<int>({5}));

    return 0;
}
