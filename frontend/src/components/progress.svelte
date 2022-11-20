<script lang="ts">
	export let progress: number;
</script>

<div class="flex w-full flex-1 flex-col items-center justify-center">
	<div class="neon h-3 w-4/5 overflow-hidden rounded-full">
		<div
			class="h-3 bg-white transition-[width] duration-[10ms]"
			style={`width: ${progress}%`}
		/>
	</div>
</div>
