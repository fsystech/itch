/**
* Copyright (c) 2018, SOW (https://www.safeonline.world). (https://github.com/RKTUXYN) All rights reserved.
* @author {SOW}
* Copyrights licensed under the New BSD License.
* See the accompanying LICENSE file for terms.
*/
// 4:50 PM 11/27/2021
// by rajib chy
#ifdef _MSC_VER
#pragma once
#endif//_MSC_VER
#if !defined(_msg_type_h)
#define _msg_type_h

namespace sow_itch {

	// System Event Message Section 4.1
	// Start of System hours. This message indicates that
	// NASDAQ is open and ready to start accepting orders.
	const char msg_type_system_event_accept_order[] = "S";

	// System Event Message Section 4.1
	// Start of Messages. Outside oftime stamp messages,
	// the start of day message is the first message sent in any trading day.
	const char msg_type_system_event_start_message[] = "O";
	
	// System Event Message Section 4.1
	// Start of Market hours. This message is intended to indicate
	// that Market Hours orders are available for execution.
	const char msg_type_system_event_start_market_hour[] = "M";
	
	// System Event Message Section 4.1
	// End of System hours. It indicates that Nasdaq is now closed and
	// will not accept any new orders today. It is still possible to
	// receive Broken Trade messages and Order Delete messages after the End of Day
	const char msg_type_system_event_end_of_hour[] = "E";
	
	// System Event Message Section 4.1
	// End of Messages. This is always the last message sent in any trading day
	const char msg_type_system_event_end_of_message[] = "C";
	
	// Stock Directory Message. Section 4.2.1
	// At the start of each trading day, Nasdaq disseminates stock directory messages for all active symbols in the Nasdaq execution system.
	const char msg_type_stock_directory[] = "R";
	
	// Stock Trading Action Message. Section 4.2.2
	// Nasdaq uses this administrative message to indicate the current trading status of a security to the trading community.
	const char msg_type_stock_trading_action[] = "H";
	
	// Reg SHO Short Sale Price Test Restricted Indicator. Section 4.2.3
	// In February 2011, the Securities and Exchange Commission (SEC) implemented changes to Rule 201 of the 
	// Regulation SHO (Reg SHO). For details, please referto SEC Release Number 34-61595. In association with 
	// the Reg SHO rule change, Nasdaq will introduce the following Reg SHO Short Sale Price Test Restricted 
	// Indicator message format
	const char msg_type_short_sale_indicator[] = "Y";
	
	// Market Participant Position message. Section 4.2.4
	// At the start of each trading day, Nasdaq disseminates a spin of market participant position messages. The 
	// message provides the Primary MarketMaker status, Market Maker mode and Market Participant state for 
	// each Nasdaq market participant firm registered in an issue. Market participant firms may use these fields to 
	// comply with certain market place rules.
	const char msg_type_market_position[] = "L";
	
	// Market wide circuit breaker Decline Level Message. Section 4.2.5.1
	// Informs data recipients what the daily MWCB breach points are set to for the current trading day
	const char msg_type_circuit_breaker_decline[] = "V";
	
	// Market Wide Circuit Breaker Status message. Section 4.2.5.2
	// Informs data recipients when a MWCB has breached one of the established levels
	const char msg_type_circuit_breaker_status[] = "W";
	
	// IPO Quoting Period Update Message. Section 4.2.6
	// Indicates the anticipated IPO quotation release time of a security
	const char msg_type_ipo_quoting_period[] = "K";
	
	// Limit Up-Limit Down( LULD ) Auction Collar. Section 4.2.7
	// Indicates the auction collar thre sholds within which a paused security can reopen following a LULD Trading Pause
	const char msg_type_limit_up_down[] = "J";
	
	// Operational Halt. Section 4.2.8
	// The Exchange uses this message to indicate the current Operational Status of
	// a security to the trading community. An Operational Halt means that there has been
	// an interruption of service on the identified security impacting only the designated Market
	// Center. These Halts differ from the "Stock Trading Action" message types since an
	// Operational Halt is specific to the exchange for which it is declared, and does not
	// interrupt the ability of the trading community to trade the identified instrument
	// on any other market place.
	const char msg_type_operational_halt[] = "h";
	
	// Add Order-No MPID Attribution. Section 4.3.1
	// An Add Order Message indicates that a new order has been accepted by the Nasdaq system and was added to the 
	// displayable book. The message includes a day unique Order Reference Number used by Nasdaq to track the order.
	const char msg_type_add_order[] = "A";
	
	// Add Order with MPID Attribution. Section 4.3.2
	// This message will be generated for attributed
	// orders and quotations accepted by the Nasdaq system
	const char msg_type_add_order_accepted[] = "F";
	
	// Order Executed Message. Section 4.4.1
	// This message is sent when ever an orderon the book is executed in whole or in part. Itis possible to receive several 
	// Order Executed Messages for the same order reference number if that order is executed in several parts. The 
	// multiple Order Executed Messages on the same order are cumulative
	const char msg_type_multiple_order_executed[] = "E";
	
	// Order Executed With Price Message. Section 4.4.2
	// This message issent whenever an order on the book is executed in whole or in part at a price different from the 
	// initial display price. Since the execution price is different than the display price of the original Add Order, Nasdaq
	// includes a price field within this execution message.
	const char msg_type_order_executed_with_price[] = "C";
	
	// Order Cancel Message. Section 4.4.3
	// This message is sent whenever an order on the book is modified as a result of a partial cancellation
	const char msg_type_order_cancel[] = "X";

	// Order Delete Message. Section 4.4.4
	// This message is sent when ever an orderon the book is being cancelled. All remaining shares are no longer accessible
	// so the order must be removed fromthe book.
	const char msg_type_order_delete[] = "D";

	// Order Replace Message. Section 4.4.5
	// This message is sent whenever an order on the book has been cancel replaced. All remaining shares from the
	// original order are no longer accessible, and must be removed. The new order details are provided for the
	// replacement, along with a new order reference number which will be used henceforth. Since the side, stock
	// symbol and attribution( if any ) can not be changed by an Order Replace event, these fields are not included in the
	// message. Firms should retain the side, stock symbol and MPID from the original Add Order message.
	const char msg_type_order_replace[] = "U";
	
	// Trade Message( Non- Cross ). Section  4.5.1
	// The Trade Message is designed to provide execution details for normal match events involving non - displayable
	// order types. (Note: There is a separate message for Nasdaq cross events.)
	const char msg_type_trade_non_cross[] = "P";

	// Cross Trade Message. Section 4.5.2
	// Cross Trade message indicates that Nasdaq has completed its cross processfor a specific security. Nasdaq sends out 
	// a Cross Trade message for all active issues in the system following the Opening, Closing and EMC cross events. Firms 
	// may use the Cross Trade message to determine when the cross for each security has been completed. (Note: For 
	// the halted / paused securities, firms should use the Trading Action message to determine when an issue has been 
	// released for trading.)
	const char msg_type_trade_cross[] = "Q";

	// Broken Trade / Order Execution Message. Section 4.5.3
	// The Broken Trade Message is sent whenever an execution on Nasdaq is broken. An execution may be broken if it is 
	// found to be "clearly erroneous" pursuantto Nasdaqs Clearly Erroneous Policy.A trade break is final; once a trade is 
	// broken, it cannot be reinstated.
	const char msg_type_broken_trade[] = "B";

	// Net Order Imbalance Indicator (NOII) Message. Section 4.6
	// Nasdaq begins disseminating Net Order Imbalance Indicators (NOII) at 9:25 a.m. for the Opening Cross and  3:50 p.m. for the Closing Cross.
	const char msg_type_order_noii[] = "I";
	
	// Retail Price Improvement Indicator(RPII). Section 4.7
	// Identifies a retail interest indication of the Bid, Ask or both the Bid and Ask for Nasdaq-listed securities.
	const char msg_type_rpii[] = "N";
  // session event
  const char msg_type_login_request[] = "L"; // to server
	const char msg_type_login_accepted[] = "A"; // from server
	const char msg_type_login_rejected[] = "J"; // from server
	const char msg_type_logout_request[] = "O"; // to server
	const char msg_type_sequenced_data[] = "S"; // from server
	const char msg_type_server_heartbeat[] = "H"; // from server
	const char msg_type_end_of_session[] = "Z"; // from server
	const char msg_type_unsequenced_data[] = "U"; // from server
	const char msg_type_client_heartbeat[] = "R"; // to server

}
#endif //!_msg_type_h
