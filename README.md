# A Limit Order Book (LOB) implemented in C++

## Available Client Commands

### buy \<security_id> \<volume> \<price>
Given a dense order book, most buy operations will be completed in **O(1)** time. However, if the book is very sparse, more often than not the worst-case time complexity of **O(log n)** applies. This is due to the need for an insertion of a new limit into the heap which takes **O(log n)** time, where n represents the number of limits in the heap.

Returns: 
1) The amount of the desired volume that was able to be filled (E.g. 10 shares of 50 were able to be bought immediately, the remaining 40 reside in the order book waiting for a counter-party).
2) The order_id

### sell \<security_id> \<volume> \<price>
The same as above applies for a sell operation.

Returns: 
1) The amount of the desired volume that was able to be filled (E.g. 10 shares of 50 were able to be sold immediately, the remaining 40 reside in the order book waiting for a counter-party).
2) The order_id

### cancel \<security_id> \<order_id>
Unless the order to be canceled is the only order at a given limit, this operation takes **O(1)** time and **O(log n)** otherwise, where n is the number of limits in the heap. Again, this is because if we are canceling the only order at a limit, we also need to remove that limit from the heap which takes **O(log n)** time.

Returns: 
1) Whether the cancellation was successful or not.

### spread \<security_id>
This operation takes **O(1)** time.

Returns: 
1) The spread for the given security, -1 if there is no best bid & ask for the security.

### volume \<security_id> \<price>
This operation takes **O(1)** time.

Returns: 
1) The volume at the given limit price.

### bestbid \<security_id>
This operation takes **O(1)** time.

Returns: 
1) The best bid for the given security, -1 if there is no best bid for the security.

### bestask \<security_id>
This operation takes **O(1)** time.

Returns: 
1) The best ask for the given security, -1 if there is no best ask for the security.

### orders \<security_id>
This operation takes **O(1)** time.

Returns:
1) The number of outstanding orders for the given security.

### quit
This command will close the connection with the server and end the client program.

## Notes

The server that uses the LOB to create a miniature "securities market/exchange" is multithreaded, so different clients can execute their orders at the same time (given that they are buying/selling different securities).

Furthermore, due to implementation details such as storing the best bid & ask in a separate variable (as opposed to always reading it from the root of the heap), and the use of mutexes, this program supports simultaneous reading and writing. So even if we are in the worst-case scenario of a buy/sell/cancel taking **O(log n)** time, other clients can still perform the read operations at the same time without having to wait.
