# 🏦 Bank Management System (C++)
A secure, production-grade console application built from scratch in C++ to automate banking system workflows. This software orchestrates a multi-user environment backed by dynamic permissions using bitwise masking operations. It features persistence via file handling, strict field validations, and custom transactional execution scopes for deposits, withdrawals, and ledger tracking.
This project represents advanced application formatting focusing on **structured programming, file stream engineering, bitwise operators, security matrices, and modular structural data pipelines.**
---
## 📚 Training Source
This project was developed as part of the training roadmap on:
**Programming Advices Platform** **Instructor:** Dr. Mohammed Abu-Hadhoud  
🔗 [https://programmingadvices.com/](https://programmingadvices.com/)
---
## 🎯 Project Objectives
* **Implement** a production-style file data architecture using flat-file text parsing.
* **Master** binary token access control using custom structural arrays and bitwise arithmetic (`&`).
* **Design** rigorous defensive data validation gates (regex-style formatting arrays via `isalpha`/`isdigit`).
* **Manage** financial balance integrity locks to completely prevent overdraft leakage during operations.
* **Architect** isolated sub-menus separating standard transactions from user configuration pipelines.
---
## ✨ Features
### 🔐 User & Security Control
* **Secure Authentication:** Gate-checked logins verifying records asynchronously against file streams.
* **Bitwise Permissions:** Custom granular administrative roles (List Clients, Add, Delete, Update, Find, Transactions, Manage Users).
* **Super-Admin Option:** Access shortcuts mapped to an global bypass condition (`-1`).
### 💼 Client Management Database
* **Structured Records System:** Complete profile logs saving data using custom data splitters (`//`).
* **Input Validation Core:** Real-time data filtration blocking invalid pin-codes, name structures, or phone configurations.
* **Full CRUD Operations:** Seamless addition, retrieval, dynamic modifications, and marked/soft deletions of client rows.
### 💸 Transaction Terminal
* **Deposit Processing:** Real-time checking and updating balances upon positive injections.
* **Withdrawal Safeguards:** Native checking algorithms assessing sufficient liquidity prior to record saving.
* **Ledger Overview:** Aggregate lists reflecting full database balances.
---
## 🧠 Concepts Applied
* **Bitwise Permission Architecture:** Utilizing progressive power values ($1, 2, 4, 8, 16, \dots$) mapped against runtime masking checks.
* **Data Record Serializers:** Hand-crafted splitters (`SepliterString`) to convert complex struct models into parsed line strings and vice versa.
* **Dynamic Memory Tracking (`vector`):** Utilizing STL containers for fluid sorting, filtering, and rapid saving of records.
* **Two-Layer TXT DB Management:** Handling independent data environments for `clint.txt` and `user.txt` concurrently.
* **Fail-Safe Formatting Hooks:** Cleansing stream state inputs (`cin.clear()`) to maintain terminal loop stability.
---
## ⚙️ Security Matrix (Bitwise Permissions)
The application evaluates user authorization based on cumulative integer masking scores:

| Permission Domain | Binary Enum Position | Bitwise Mask Value |
| :--- | :--- | :--- |
| **Full Admin Bypass** | `All` | `-1` |
| **List Clients Ledger** | `Lestcleint` | `1` |
| **Add New Clients** | `Addcleint` | `2` |
| **Delete Client Profile** | `Deletcleint` | `4` |
| **Update Client Records** | `Updetcleint` | `8` |
| **Find Specific Account** | `Findcleint` | `16` |
| **Financial Transactions Menu** | `Transaction` | `32` |
| **Manage User Databases** | `Manangusers` | `64` |

---
## 🕹️ System Architecture Map
The application routes data sequentially across isolated logical segments:
1. **`Login()` Gate:** Instantiates dynamic parameters and maps credentials to the global pointer object `correntuser`.
2. **`ShowMainMenue()`:** Acts as the primary terminal switchboard routing control safely to sub-modules.
3. **`Show_transaction_menue()`:** Holds transaction execution routines while monitoring token status permissions.
4. **`Show_Manang_User()`:** Hosts the sub-system layer allowing root admins to edit standard banking personnel profiles.
5. **Data Commits:** Writes updated memory vectors directly to persistence nodes (`clint.txt` / `user.txt`) using dynamic date-stamps.
---
## 🖥️ System Output Previews
### Login Sequence
```text
                        Bank Management System
                        ----------------------
                        Username: Admin
                        Password: ••••••
