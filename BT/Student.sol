// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.8.2 <0.9.0;

contract StudentData {
    // Structure representing a student
    struct Student {
        int id;
        string name;
        int age;
        string dept;
    }

    // Array to store all the student ids
    int[] public studentIds;

    // Map to store all the student's information
    mapping(int => Student) public students;

    // Event to notify the addtion of a student
    event NewStudentAdded(int indexed _id, string  _name, int _age, string  _dept);

    function addStudent(int _id, string memory _name, int _age, string memory _dept) external {
        // Creating new student
        Student memory stud = Student({
            id: _id,
            name: _name,
            age: _age,
            dept: _dept
        });

        studentIds.push(_id);

        students[_id] = stud;

        emit NewStudentAdded(_id, _name, _age, _dept);
    }

    function getStudent(int _id) view external returns(int, string memory, int, string memory){
        Student memory stud = students[_id];

        return (stud.id, stud.name, stud.age, stud.dept);
    }

    fallback(bytes calldata) external payable returns(bytes memory){
        return("Fallback called !");
    }

    receive() external payable  {

    }
}