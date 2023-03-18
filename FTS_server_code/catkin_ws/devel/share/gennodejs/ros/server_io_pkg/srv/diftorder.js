// Auto-generated. Do not edit!

// (in-package server_io_pkg.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class diftorderRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.option = null;
    }
    else {
      if (initObj.hasOwnProperty('option')) {
        this.option = initObj.option
      }
      else {
        this.option = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type diftorderRequest
    // Serialize message field [option]
    bufferOffset = _serializer.uint16(obj.option, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type diftorderRequest
    let len;
    let data = new diftorderRequest(null);
    // Deserialize message field [option]
    data.option = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a service object
    return 'server_io_pkg/diftorderRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'af74275f9217ebe12d60559909b3a954';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint16 option
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new diftorderRequest(null);
    if (msg.option !== undefined) {
      resolved.option = msg.option;
    }
    else {
      resolved.option = 0
    }

    return resolved;
    }
};

class diftorderResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.state = null;
    }
    else {
      if (initObj.hasOwnProperty('state')) {
        this.state = initObj.state
      }
      else {
        this.state = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type diftorderResponse
    // Serialize message field [state]
    bufferOffset = _serializer.uint16(obj.state, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type diftorderResponse
    let len;
    let data = new diftorderResponse(null);
    // Deserialize message field [state]
    data.state = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a service object
    return 'server_io_pkg/diftorderResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '891b541ef99af7889d0f22a062410be8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint16 state
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new diftorderResponse(null);
    if (msg.state !== undefined) {
      resolved.state = msg.state;
    }
    else {
      resolved.state = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: diftorderRequest,
  Response: diftorderResponse,
  md5sum() { return 'e02c72c1210af7da24f1a6fd961ebe93'; },
  datatype() { return 'server_io_pkg/diftorder'; }
};
