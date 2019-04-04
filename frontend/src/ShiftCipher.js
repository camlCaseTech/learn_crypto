import React, { Component } from "react";

let asciiCode = (textCode, offset) => {
  if (textCode === undefined) return;
  let codeArray = [];
  for (var i = 0; i < textCode.length; i++) {
    let textUpper = textCode.toUpperCase();
    if (textUpper.charCodeAt(i) >= 65 && textUpper.charCodeAt(i) <= 90) {
      let asciiOffset =
        (parseInt(textUpper.charCodeAt(i)) + parseInt(offset) + 13) % 26;
      let codeStr = String.fromCharCode(asciiOffset + 65);
      codeArray.push(codeStr);
    } else {
      codeArray.push(String.fromCharCode(32));
    }
  }
  return codeArray;
};

let zeroPad = num => {
  return "00000000".slice(String(num).length) + num;
};

let toBinary = (str, spaceSeparatedOctets) => {
  let binary = [];
  return str.replace(/[\s\S]/g, function(str) {
    str = zeroPad(str.charCodeAt().toString(2));
    return !1 === spaceSeparatedOctets
      ? binary.push(str)
      : binary.push(str + " ");
  });
};

let toAscii = function(bin) {
  return bin.replace(/\s*[01]{8}\s*/g, function(bin) {
    return String.fromCharCode((parseInt(bin, 2) % 26) + 65);
  });
};

class ShiftCipher extends Component {
  constructor(props) {
    super(props);
    this.state = {
      offset: "",
      textCode: "",
      binary: ""
    };
    this.handleChangeOffset = this.handleChangeOffset.bind(this);
    this.handleChangeTextCode = this.handleChangeTextCode.bind(this);
  }

  handleChangeOffset(event) {
    let offset = event.target.value;
    let codeArray = asciiCode(this.state.textCode, offset);
    let binary = toBinary(codeArray.join(""), 0);
    console.log("binary", binary);
    this.setState({ binary, offset });
  }

  handleChangeTextCode(event) {
    // asciiCode(textCode, offset); charFrequency(codeArray); toBinary(codeArray.join(''), 0);" />
    let textCode = event.target.value;
    let codeArray = asciiCode(textCode, this.state.offset);
    let binary = toBinary(codeArray.join(""), 0).join("");
    this.setState({ binary, textCode });
  }

  render() {
    return (
      <div className="ShiftCipher">
        <h3>Type a sentence and it will be converted to binary.</h3>
        <form>
          <label>
            <input
              type="text"
              size="10"
              onChange={this.handleChangeOffset}
              value={this.state.offset}
            />
            Offset
          </label>
          <br />
          <input
            type="text"
            size="60"
            onChange={this.handleChangeTextCode}
            value={this.state.textCode}
          />
        </form>
        <h3>Binary</h3>
        <p>{this.state.binary}</p>
      </div>
    );
  }
}

export default ShiftCipher;
