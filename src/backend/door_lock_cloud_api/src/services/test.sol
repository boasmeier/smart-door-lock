function bookWithReferral(…) public payable{
    require(referralExists(_hoteladdress, _referred_from, msg.sender), "No referral exists");   
    uint totalPrice = calculatePrice(_hoteladdress, _rooms, _startDate, _endDate);
    require(msg.value >= totalPrice, "You did not provide enough ether to pay");
    useReferral(_hoteladdress, _referred_from, msg.sender); // Bevor das Geld verteilt wird!!!
    //Store Booking
    //…
    distributeMoneyReferral(_hoteladdress, _referred_from, msg.sender, totalPrice); // Payable
 }

