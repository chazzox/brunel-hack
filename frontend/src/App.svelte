<script lang="ts">
	import Heart from './assets/heart.svelte';
	import Logo from './assets/logo/index.svelte';

	import Progress from './components/progress.svelte';
	import classnames from 'classnames';
	import { onMount } from 'svelte';
	import GameOver from './components/gameOver.svelte';

	interface Payload {
		state: number;
		stop: 'ddosing me you';
	}

	let userIsCorrect = true;
	let userText = '';
	let socket: WebSocket | null = null;

	let hasGameEnded = false;
	let didBeginTyping = false;
	// game state
	let score = 0;
	let progress = 100;
	const wordLength = 10;
	let words: string[] = [];
	let rate = !userIsCorrect ? 0.35 : 0.1;
	$: rate = !userIsCorrect ? 0.35 : 0.1;

	const getWords = ({ length }: { length: number }) => {
		const validInputs = ['⬆️', '⬇️', '⬅️', '➡️'];
		const output = [];

		for (let i = 0; i < length; i++) {
			output.push(validInputs[Math.floor(validInputs.length * Math.random())])
		}

		return output;
	};

	const makeSocket = () => {
		socket = new WebSocket('ws://192.168.230.138:80/dance');
	};

	const handleChar = (char: string) => {
		console.log(`Got ${char}, wordlist ${words.join(" ")}`)

		if (words[0] === char) {
			score++;
			words = [words[1], words[2], words[3], words[4], words[5], words[6], words[7], words[8], words[9], ...getWords({ length: 1 })]
		}
	};

	const addInput = (input: number) => {
		if (input) didBeginTyping = true;
		if (hasGameEnded) return;

		if (input & (1 << 0)) handleChar('🈚');
		if (input & (1 << 1)) handleChar('🈷️');
		if (input & (1 << 2)) handleChar('❌');
		if (input & (1 << 3)) handleChar('⭕');
		if (input & (1 << 4)) handleChar('⬆️');
		if (input & (1 << 5)) handleChar('⬅️');
		if (input & (1 << 6)) handleChar('➡️');
		if (input & (1 << 7)) handleChar('⬇️');
	};

	onMount(async () => {
		words = getWords({ length: 10 });

		makeSocket();

		socket.addEventListener('open', () => {
			console.log('Opened');

			const interval = setInterval(() => {
				if (socket) {
					console.log('sending awoo');
					socket.send('awoo');
				}

				if (hasGameEnded) {
					clearInterval(interval);
					socket.close();
				}
			}, 100);
		});

		socket.addEventListener('close', makeSocket);
		socket.addEventListener('error', makeSocket);

		socket.addEventListener('message', (e) => {
			console.log(e);

			const payload = JSON.parse(e.data) as Payload;

			addInput(payload.state);
		});
	});

	$: if (words.length > 0) {
		userIsCorrect = words.join(' ').startsWith(userText);
		console.log(userIsCorrect, words, userText);
	}

	const gameOver = () => {
		hasGameEnded = true;
	};

	function step() {
		progress = Math.max(0, progress - rate);

		if (progress < 0.01) gameOver();
		else requestAnimationFrame(step);
	}

	$: if (didBeginTyping) requestAnimationFrame(step);
</script>

{#if !hasGameEnded}
	<main
		class={classnames(
			'flex min-h-screen flex-col items-center bg-black p-10 text-white',
			!userIsCorrect && 'neonIn'
		)}
	>
		<Logo />
		<div class="mx-auto text-white/80"><p>user score: {score}</p></div>

		<div class="flex flex-1 flex-col items-center justify-center gap-24 text-6xl">
			<p>{words.join(' ')}</p>
		</div>

		<Progress {progress} />

		<div
			class={classnames(
				'my-10 flex h-16 w-11/12 items-center rounded-xl bg-zinc-900 p-2',
				userIsCorrect ? 'shadow-xl shadow-white/10' : 'neon'
			)}
		>
			<input
				on:keydown={(e) => {
					didBeginTyping = true;
					// if (e.key == 'Enter') handleEnterPress();
				}}
				bind:value={userText}
				disabled={hasGameEnded}
				placeholder="enter phrase"
				type="text"
				class="h-full w-full rounded-xl bg-black px-3 text-center
	font-bold outline-none transition-colors duration-300 hover:bg-white/20"
			/>
		</div>
		<div class="mx-auto my-2 text-white/60"
			>made with <Heart classes="h-4 inline-block" /> by shitposting ltd</div
		>
	</main>
{:else}
	<GameOver {score} />
{/if}

<style>
	:global(.neon) {
		box-shadow: 0 0 2rem #dc2626, 0 0 0.8rem #dc2626, 0 0 2rem #dc2626;
	}

	:global(.neonIn) {
		box-shadow: 0 0 0.2rem #fff, 0 0 0.2rem #fff, 0 0 2rem #dc2626, 0 0 0.8rem #dc2626,
			0 0 2.8rem #dc2626, inset 0 0 1.3rem #dc2626;
	}
</style>
