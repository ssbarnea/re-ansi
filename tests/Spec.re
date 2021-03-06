let withColor = (color, rest) =>
  Ansi.DocStyle(ReactDOM.Style.make(~color, ()), rest);

let withFont = (style, rest) =>
  Ansi.DocStyle(ReactDOM.Style.make(~fontWeight=style, ()), rest);

let testParse = (txt, expected) => {
  let parsed = txt->Ansi.parse;
  parsed == expected
    ? true
    : {
      Js.log3(txt, "!=", expected);
      false;
    };
};

let spec = [
  "Copying blob 15de\r\n\x1b[1A\x1b[JCopied"->testParse([Text("Copied")]),
  "bold: \x1b[1mtest\x1b[0m"
  ->testParse([Text("bold: "), withFont("bold", [Text("test")])]),
  "test: \x1b[31mr\x1b[32ma\x1b[0m"
  ->testParse([
      Text("test: "),
      withColor("red", [Text("r"), withColor("green", [Text("a")])]),
    ]),
];

Node.Process.exit(spec->Belt.List.every(x => x) ? 0 : 1);
