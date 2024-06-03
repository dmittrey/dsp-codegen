# Submodule to parse util::Register objects

Need to parse register collection from some syntax

Consists:
- Interface
- Json (Parse from json syntax logic)

# Extension

When you need to extend your parsing logic from some syntax, you need:
- Add submodule (for example. xml, csv)
- Add **header** in submodule to **declare fabric-method** signature to produce own parser
- Add **src** in submodule to **define own parser structure** that implement IRegParser interface