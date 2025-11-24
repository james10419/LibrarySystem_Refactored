📚 Custom Data Structure Library Management System

배열(Array) 기반의 선형 탐색에서 오는 성능 한계를 극복하기 위해, Hash Table과 BST(Binary Search Tree)를 바닥부터(From Scratch) 직접 구현하여 최적화한 도서관 관리 시스템입니다.

🚀 Project Overview

처음에는 단순 std::vector와 순차 탐색을 사용하여 도서 관리 시스템을 구현했습니다. 하지만 데이터가 늘어날수록 특정 도서를 찾는 속도가 현저히 느려지는 문제(O(N))를 직면했습니다.
이를 해결하기 위해 STL Container(std::map, std::unordered_map)에 의존하지 않고, 직접 자료구조를 설계하여 검색 성능을 획기적으로 개선했습니다.

Period: 2025.03.15~2025.04.20

Role: 1인 개인 프로젝트

Tech Stack: C++, STL(Vector only for memory holding)

🛠 Engineering Decisions

1. Performance Optimization (검색 속도 개선)
가장 빈번하게 일어나는 '검색' 연산의 효율성을 위해 두 가지 인덱싱 전략을 도입했습니다.


<img width="628" height="225" alt="image" src="https://github.com/user-attachments/assets/435d23c7-b70f-43d1-99b5-51dc04102d73" />


2. Memory Ownership & Decoupling (구조적 안정성)
자료구조 수업에서 배운 포인터 개념을 응용하여 데이터의 소유(Ownership)와 참조(Reference)를 분리했습니다.
LibraryManager: 실제 Book 객체의 생성과 소멸을 담당 (Memory Owner).
BST & Hash Table: 객체의 주소값(Book*)만 저장하여 메모리 중복 사용 방지 및 가벼운 인덱싱 구현.
Result: 시스템 종료 시 Manager에서 일괄적으로 메모리를 해제하여 Memory Leak 방지.

📂 Code Structure


├── main.cpp            # Entry point & UI Loop

├── Book.h              # Data Domain

├── HashTable.h         # ID Search Implementation (Chaining)

├── BST.h               # Title Search Implementation (Recursive)

└── LibraryManager.h    # Facade Class handling logic


(참고: 본 리포지토리는 단일 파일 library_system.cpp로 통합되어 있습니다.)
💻 How to Run
별도의 외부 라이브러리 없이 표준 C++ 컴파일러만 있으면 실행 가능합니다.


📝 Learning Points
이 프로젝트를 통해 다음과 같은 엔지니어링 감각을 익혔습니다.
자료구조의 Trade-off: 해시 테이블은 빠르지만 공간 복잡도가 높고, BST는 정렬이 되지만 트리의 균형이 중요하다는 점을 체감.
Pointer & Memory Management: 이중 해제(Double Free) 오류를 디버깅하며 객체의 생명주기 관리의 중요성 학습.
Created by [유영준]
