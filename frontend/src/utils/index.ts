export function debounce(inputFunction, timeToWaitBeforeFiringInMs = 500) {
	let timer;
	return (...args) => {
		clearTimeout(timer);
		timer = setTimeout(() => {
			inputFunction.apply(this, args);
		}, timeToWaitBeforeFiringInMs);
	};
}

export function stopTyping(node) {
	const handleKeyup = debounce((event: KeyboardEvent) => {
		// (1) the debounce logic
		if (node.contains(event.target)) {
			// (2) restrict the event to the only referring node
			node.dispatchEvent(new CustomEvent('stopTyping')); // (3) fire the event
		}
	}, 3000);

	// (4) add a generic keyup event
	document.addEventListener('keyup', handleKeyup, true);

	return {
		destroy() {
			// (5) cleanup on destroy
			document.removeEventListener('keyup', handleKeyup, true);
		}
	};
}
