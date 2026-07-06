# GitHub Simulation (C++)

A desktop GitHub-like simulation built in C++ (Windows Forms / C++/CLI) on top of hand-written data structures — no STL containers for the core model. Users can register, log in, create repositories, add files and commits, fork public repositories, follow other users, and browse profiles, with all state persisted to CSV files between sessions.

## Data Structures

Every core entity is backed by a data structure implemented from scratch:

| Concern | Structure | Where |
| --- | --- | --- |
| Repositories per user | Binary search tree (keyed by repo name) | `Repository.h` |
| Files per repository | Singly linked list | `File.h` |
| Commits per file | Linked list (`CommitList`) | `Commit.h` |
| Follow relationships | Graph (adjacency representation) | `SocialNetwork.h` |
| Users | Custom user table with validation | `User.h`, `Validation.h` |
| Errors | Custom exception hierarchy | `exception.h` |

## Features

- User registration and login with input validation
- Create public/private repositories; fork public repositories (fork counts tracked)
- Add files to repositories and commits to files
- Follow/unfollow users and view follower relationships
- Search users and browse their public repositories
- CSV persistence for users, repositories, files, commits, and the follow graph (`users.csv`, `FollowRelationships.csv`, per-user repo CSVs)

## Build

Open `GithubSimulation.sln` in Visual Studio (C++/CLI, Windows Forms) and build. The sample CSV files in the repository root provide seed data.

## Notes

Built as a university Data Structures semester project — the goal was implementing and composing the underlying structures (BST, linked lists, graph) rather than using library containers.
