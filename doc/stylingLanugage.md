Styling language.
JSON version of css

supported attributes and values:
`display: <relative, absolute>`
`xpos: <int>`
`ypos: <int>`
`width: <int>`
`height: <int>`
`padding: <int>`
`margin: <int>`
`font-color: -[0-255, 0-255, 0-255]`


Local Constants:
PARENT_WIDTH,
PARENT_HEIGHT,
PARENT_Z,
NUMBER_OF_SIBLINGS
POSITION:

Logical operations:
Must be in a `{{expression}}`
`+: add 2 integer values together`
`-: subtract 2 values together`
`*: times 2 values together`
`divide: times 2 values together`

example:

.btn {

}

.col-4 {
    xpos: {{ PARENT_WIDTH / NUMBER_OF_SIBLINGS}}
}