#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Player {
    string name;
    string role;
    int basePrice;
    int soldPrice;
    string team;
    bool sold;
    vector<int> bidHistory;

public:
    Player(string name, string role, int basePrice) 
        : name(name), role(role), basePrice(basePrice), soldPrice(0), team("Unsold"), sold(false) {}

    void setSoldPrice(int price) {
        soldPrice = price;
        sold = true;
    }

    void setTeam(string teamName) { team = teamName; }
    
    int getBasePrice() const { return basePrice; }
    
    int getSoldPrice() const { return soldPrice; }
    
    string getName() const { return name; }
    
    string getRole() const { return role; }
    
    string getTeam() const { return team; }
    
    bool isSold() const { return sold; }

    void addBidToHistory(int bid) { bidHistory.push_back(bid); }

    void displayBidHistory() const {
        cout << "Bid History for " << name << ": ";
        for (int bid : bidHistory) {
            cout << bid << " ";
        }
        cout << endl;
    }
};

class Team {
    string name;
    int budget;
    int maxPlayers;
    int currentPlayers;
    vector<Player> squad;

public:
    Team(string name, int budget, int maxPlayers) 
        : name(name), budget(budget), maxPlayers(maxPlayers), currentPlayers(0) {}

    bool bid(Player &player, int bidAmount) {
        if (budget >= bidAmount && currentPlayers < maxPlayers) {
            budget -= bidAmount;
            player.setSoldPrice(bidAmount);
            player.setTeam(name);
            player.addBidToHistory(bidAmount);
            squad.push_back(player);
            currentPlayers++;
            return true;
        }
        return false;
    }

    int getBudget() const { return budget; }

    vector<Player> getSquad() const { return squad; }

    string getName() const { return name; }

    int getCurrentPlayers() const { return currentPlayers; }

    int getMaxPlayers() const { return maxPlayers; }

    void displayTeam() const {
        cout << "Team: " << name << "\nBudget Left: " << budget << "\nPlayers: \n";
        for (const auto &player : squad) {
            cout << player.getName() << " (" << player.getRole() << ") - " << player.getSoldPrice() << "\n";
        }
        cout << endl;
    }
};

class Auctioneer {
    vector<Player> players;
    vector<Team> teams;

public:
    Auctioneer(vector<Player> playerList, vector<Team> teamList) : players(playerList), teams(teamList) {}

    void startAuction() {
        for (auto &player : players) {
            if (!player.isSold()) {
                conductBidding(player);
            }
        }
    }

    void conductBidding(Player &player) {
        int highestBid = player.getBasePrice();
        Team* highestBidder = nullptr;
        map<Team*, int> teamBids;

        for (auto &team : teams) {
            if (team.getBudget() >= highestBid && team.getCurrentPlayers() < team.getMaxPlayers()) {
                int bidAmount;
                cout << team.getName() << ", enter your bid for " << player.getName() 
                     << " (Base Price: " << player.getBasePrice() << "): ";
                cin >> bidAmount;

                if (bidAmount >= highestBid && bidAmount <= team.getBudget()) {
                    teamBids[&team] = bidAmount;
                }
            }
        }

        if (!teamBids.empty()) {
            for (auto &entry : teamBids) {
                if (entry.second > highestBid) {
                    highestBid = entry.second;
                    highestBidder = entry.first;
                }
            }

            if (highestBidder != nullptr && highestBidder->bid(player, highestBid)) {
                announceWinner(player, *highestBidder);
            }
        } else {
            cout << player.getName() << " remains unsold.\n";
        }
    }

    void announceWinner(Player &player, Team &team) {
        cout << "Player " << player.getName() << " sold to " << team.getName() 
             << " for " << player.getSoldPrice() << endl;
    }

    void displayUnsoldPlayers() const {
        cout << "\nUnsold Players:\n";
        for (const auto &player : players) {
            if (!player.isSold()) {
                cout << player.getName() << " (" << player.getRole() << "), Base Price: " << player.getBasePrice() << endl;
            }
        }
        cout << endl;
    }

    void displayTeamSummary() const {
        for (const auto &team : teams) {
            team.displayTeam();
        }
    }
};

int main() {
    vector<Player> players = { 
        Player("Virat Kohli", "Batsman", 200), 
        Player("Rohit Sharma", "Batsman", 150), 
        Player("Jasprit Bumrah", "Bowler", 120),
        Player("MS Dhoni", "Wicketkeeper", 180),
        Player("Ben Stokes", "All-rounder", 250)
    };

    vector<Team> teams = { 
        Team("Mumbai Indians", 500, 3), 
        Team("Chennai Super Kings", 450, 3)
    };

    Auctioneer auction(players, teams);
    auction.startAuction();

    auction.displayUnsoldPlayers();
    auction.displayTeamSummary();

    return 0;
}