// SPDX-License-Identifier: GPL-3.0

pragma solidity  >=0.7.0 <0.9.0;

contract Bank {
    mapping(address => uint) public user_account; // [user, balance]
    mapping(address => bool) public user_exists; // [user, isExists]

    // Modifier to check is if the user exists
    modifier checkUser() {
        require(user_exists[msg.sender] == true, "!!! ACCOUNT NOT CREATED !!!");

        _;
    }

    function create_account() public payable returns(string memory) {
        require(user_exists[msg.sender] == false, "!!! ACCOUNT ALREADY EXISTS !!!");
        
        user_account[msg.sender] = msg.value;
        user_exists[msg.sender] = true;

        return "Account created successfully !";    
    }

    function deposit(uint amount) public payable checkUser returns(string memory) {
        require(amount > 0, "!!! Ammount should be more than 0 !!!");

        user_account[msg.sender] += amount;

        return "Amount deposited successfully !";
    } 

    function withdraw(uint amount) public payable checkUser returns(string memory) {
        require(amount > 0, "!!! Ammount should be more than 0 !!!");
        require(user_account[msg.sender] >= amount, "!!! Insufficient account balance !!!");

        user_account[msg.sender] -= amount;

        return "Amount withdrawn successfully !";
    }

    function check_balance() public view checkUser returns(uint) {
        return user_account[msg.sender];
    }

    function account_exists() public view returns(string memory) {
        return user_exists[msg.sender] == true ? "Account exists" : "Account does not exists";
    }

}