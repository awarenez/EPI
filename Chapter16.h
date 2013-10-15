//
//  Chapter16.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/5/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter16__
#define __EPI__Chapter16__

#include <iostream>
#include <vector>
#include <queue>
#include <array>

using namespace std;

// 16.1
struct Coordinate {
    int x, y;
    const bool operator==(const Coordinate &that) const {
        return (x == that.x && y == that.y);
    }
};
    
bool is_feasible(const Coordinate &current, vector<vector<int>> maze) {
    return (current.x >= 0 && current.x < maze.size() &&
            current.y >= 0 && current.y < maze[current.x].size() &&
            maze[current.x][current.y] == 0);
}

// DFS
bool search_maze_helper(vector<vector<int>> maze, const Coordinate &cur, const Coordinate &e, vector<Coordinate> path) {
    if (cur == e) return true;
    // search up, down, left, right
    const array<array<int, 2>, 4> shifts = {{{{0, 1}}, {{0, -1}}, {{1, 0}}, {{-1, 0}}}};
    for (const auto &s : shifts) {
        Coordinate next{cur.x + s[0], cur.y + s[1]}; // find the neeightbor
        if (is_feasible(next, maze)) {
            maze[next.x][next.y] = 1;
            path.emplace_back(next);
            if (search_maze_helper(maze, next, e, path)) {
                return true;
            }
            path.pop_back();
        }
    }
    return false;
}
    
template<typename T>
vector<Coordinate> search_maze(vector<vector<int>> maze, const Coordinate &s, const Coordinate &e)
{
    vector<Coordinate> path;
    
    maze[s.x][s.y] = 1;
    path.emplace_back(s);
    
    if (search_maze_helper(maze, s, e, path) == false)
        path.pop_back();
    
    return path;
}

#endif /* defined(__EPI__Chapter16__) */
