const tailwind = require('prettier-plugin-tailwindcss');
const organizeImports = require('prettier-plugin-organize-imports');

const plugins = [
	{
		...tailwind,
		parsers: {
			...tailwind.parsers,
			...Object.keys(organizeImports.parsers).reduce((acc, key) => {
				acc[key] = {
					...tailwind.parsers[key],
					preprocess(code, options) {
						return organizeImports.parsers[key].preprocess(code, options);
					}
				};
				return acc;
			}, {})
		}
	}
];

/**
 * @type {import('@types/prettier').Options}
 */
module.exports = {
	plugins,
	useTabs: true,
	tabWidth: 4,
	singleQuote: true,
	trailingComma: 'none',
	printWidth: 100,
	htmlWhitespaceSensitivity: 'strict',
	// import sort config
	importOrder: ['<THIRD_PARTY_MODULES>', '^[./]', '^[../]'],
	importOrderSeparation: true,
	overrides: [
		{
			files: '*.svelte',
			options: {
				parser: 'svelte'
			}
		}
	]
};
