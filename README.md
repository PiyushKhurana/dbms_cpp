### Explanation:

1. **Table Class**:  
   - This class represents a table in the database. It stores rows as a vector of unordered maps where the key represents column names, and the value represents the cell data. 
   - It supports basic CRUD operations: `insert`, `update`, `deleteRow`, and `select`.

2. **Database Class**:  
   - Manages a collection of tables. It provides methods to create tables, retrieve a table, and execute queries using a handler class.

3. **QueryHandler and Derived Classes**:  
   - `QueryHandler` is an abstract base class that provides an interface for executing SQL-like queries.
   - Specific query types (Insert, Update, Delete, and Select) are implemented as subclasses of `QueryHandler`.

4. **CRUD Operations**:  
   - Insert, update, delete, and select operations are demonstrated using respective query handlers that are executed on the `Database` instance.







More Description:

1. **Classes:**
   - **Table Class**: Represents a table in the database. It stores rows (data), and each row is a dictionary of key-value pairs (column name and value). Arrows from `Table` will point to `Rows` to show the data it holds.
   - **Database Class**: Manages multiple tables. There is an arrow from `Database` to `Table` indicating that a `Database` contains multiple `Tables`.
   - **QueryHandler**: This is an abstract class that defines a common interface for executing queries. It is a parent class for different types of queries (Insert, Update, Delete, Select).
   - **InsertQueryHandler, UpdateQueryHandler, DeleteQueryHandler, SelectQueryHandler**: These are derived classes of `QueryHandler` and represent the implementation of specific SQL queries. They interact with the `Table` class to perform CRUD operations.

2. **Relationships:**
   - The **Database** class contains multiple **Table** instances, so there’s a one-to-many relationship between `Database` and `Table`.
   - The **QueryHandler** class is the base class for all query types, and it interacts with the **Table** class to manipulate data.
   - Each specific **QueryHandler** (Insert, Update, Delete, Select) directly interacts with a `Table` to execute its corresponding operation.
   - **Rows** in the **Table** are represented as key-value pairs, showing that each row contains column names and values.

3. **Flow of Operations:**
   - Queries are created as specific `QueryHandler` objects (Insert, Update, Delete, or Select).
   - These `QueryHandler` objects execute the operations on a `Table` instance.
   - The **Database** executes the queries using the `executeQuery()` function.



## System architecture and the flow of operations for the in-memory DBMS:-

---


### **Explanation **

- **Database**: Manages multiple `Table` instances. It has a map `tables`, which stores `Table` objects identified by their names. The `Database` class can create new tables and execute queries.
  
- **Table**: Each `Table` stores data as `Rows` (a vector of unordered maps where keys are column names and values are data entries). It supports operations like `insert()`, `update()`, and `deleteRow()` on the data.

- **Rows**: These represent the actual data in the table in a key-value pair format (column name: value).

- **QueryHandler**: An abstract base class that defines the interface for executing queries. The derived classes (`InsertQueryHandler`, `UpdateQueryHandler`, `DeleteQueryHandler`, and `SelectQueryHandler`) implement specific query logic.

---


### **Explanation of Process Flow:**

1. **User Issues Query**: A user or program issues a query such as `INSERT`, `UPDATE`, `SELECT`, or `DELETE`.

2. **Database Receives the Query**: The query is passed to the `Database` class. The `Database` class contains multiple `Table` objects.

3. **Database Searches for Relevant Table**: Based on the query, the database searches for the table (from the map) that the query will operate on.

4. **QueryHandler Executes Query**: The `QueryHandler` object, depending on the type of query (`Insert`, `Update`, `Select`, or `Delete`), will be created and executed.

5. **QueryHandler Calls Specific Method**: Each query handler calls the relevant method (e.g., `insert()`, `update()`, `deleteRow()`, or `select()`) on the corresponding `Table`.

6. **Table Data is Manipulated**: The `Table` class will perform the requested operation on its rows (data).

7. **Table Returns Result**: After the operation, the table either updates its data, returns the selected data, or confirms the row deletion.

8. **Database Returns Response**: Finally, the `Database` returns a response to the user, such as a success or error message.

---



### Ouput

```
Inserting Data into Employees Table...
Inserting Data into Departments Table...

Employees Table after Insertion:
id: 1    name: Alice    department: HR    
id: 2    name: Bob      department: IT    

Departments Table after Insertion:
id: 1    name: HR    
id: 2    name: IT    

Updating Data in Employees Table...

Employees Table after Update:
id: 1    name: Alice Updated    department: HR    
id: 2    name: Bob              department: IT    

Deleting Data from Employees Table...

Employees Table after Delete:
id: 1    name: Alice Updated    department: HR    

```
