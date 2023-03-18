// Auto-generated. Do not edit!

// (in-package server_io_pkg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class data {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.servertime = null;
      this.serverstate = null;
      this.raw_loadcell = null;
    }
    else {
      if (initObj.hasOwnProperty('servertime')) {
        this.servertime = initObj.servertime
      }
      else {
        this.servertime = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('serverstate')) {
        this.serverstate = initObj.serverstate
      }
      else {
        this.serverstate = 0;
      }
      if (initObj.hasOwnProperty('raw_loadcell')) {
        this.raw_loadcell = initObj.raw_loadcell
      }
      else {
        this.raw_loadcell = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type data
    // Serialize message field [servertime]
    bufferOffset = _serializer.time(obj.servertime, buffer, bufferOffset);
    // Serialize message field [serverstate]
    bufferOffset = _serializer.uint16(obj.serverstate, buffer, bufferOffset);
    // Serialize message field [raw_loadcell]
    bufferOffset = _arraySerializer.uint32(obj.raw_loadcell, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type data
    let len;
    let data = new data(null);
    // Deserialize message field [servertime]
    data.servertime = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [serverstate]
    data.serverstate = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [raw_loadcell]
    data.raw_loadcell = _arrayDeserializer.uint32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.raw_loadcell.length;
    return length + 14;
  }

  static datatype() {
    // Returns string type for a message object
    return 'server_io_pkg/data';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8eafbed3b402bae6038c14d1654d8886';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time servertime
    uint16 serverstate
    uint32[] raw_loadcell
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new data(null);
    if (msg.servertime !== undefined) {
      resolved.servertime = msg.servertime;
    }
    else {
      resolved.servertime = {secs: 0, nsecs: 0}
    }

    if (msg.serverstate !== undefined) {
      resolved.serverstate = msg.serverstate;
    }
    else {
      resolved.serverstate = 0
    }

    if (msg.raw_loadcell !== undefined) {
      resolved.raw_loadcell = msg.raw_loadcell;
    }
    else {
      resolved.raw_loadcell = []
    }

    return resolved;
    }
};

module.exports = data;
