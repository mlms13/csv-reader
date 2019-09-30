// rollup.config.js
import resolve from 'rollup-plugin-node-resolve';
import commonjs from 'rollup-plugin-commonjs';
import replace from 'rollup-plugin-replace';

const reactPlugins = [
  resolve({
    jsnext: true,
    main: true
  }),
  replace({
    'process.env.NODE_ENV': JSON.stringify('production')
  }),
  commonjs({
    include: 'node_modules/**',
    namedExports: {
      'node_modules/react/index.js': [
        'Children',
        'Component',
        'PureComponent',
        'PropTypes',
        'createElement',
        'Fragment',
        'cloneElement',
        'StrictMode',
        'createFactory',
        'createRef',
        'createContext',
        'isValidElement',
        'isValidElementType',
        'useState',
        'useEffect',
        'useReducer'
      ],
      'node_modules/react-dom/index.js': [
        'render',
        'hydrate',
        'createPortal',
      ],
    }
  })
];

export default {
  input: 'src/App.bs.js',
  output: {
    name: "bundle",
    format: 'iife'
  },
  plugins: reactPlugins,
  treeshake: {
    moduleSideEffects: false
  }
};
