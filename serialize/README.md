# Submodule to serialize Layouts

Need to serialize layouts of syntax models to some output stream

Consists:
- Interface
- Generic (Main serialize logic)
- File (Serialize to file logic)

# Extension

When you need to extend your serializing logic to another output resource, you need:
- Add submodule (for example. tcp, console)
- Add **header** in submodule to **declare fabric-method** signature
- Add **src** in submodule to **define fabric-method** function that use generic level if need