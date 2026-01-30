# Issue: Add Support for Displaying `file_link` Message Type

## Summary
Add support for displaying `file_link` messages in the chat log when they are received in the stream response from the PartWise API.

## Background
The PartWise API can return `file_link` messages that contain references to collected files (such as datasheets) along with pre-signed URLs for accessing them. Currently, these messages are not displayed in the chat interface.

## Message Format
The `file_link` message has the following structure:

```json
{
    "type": "file_link",
    "data": {
        "name": "filename",
        "url": "https://..."
    },
    "project_id": "..."
}
```

### Example Message
```python
{
    'type': 'file_link',
    'data': {
        'name': 'DSPIC33EP64GP504-E%2FPT.pdf',
        'url': 'https://storage.googleapis.com/part_datasheet_bucket_large/DSPIC33EP64GP504-E%252FPT.pdf?X-Goog-Algorithm=GOOG4-RSA-SHA256&X-Goog-Credential=partwise-chat-server%40partwise.iam.gserviceaccount.com%2F20260130%2Fauto%2Fstorage%2Fgoog4_request&X-Goog-Date=20260130T190715Z&X-Goog-Expires=43200&X-Goog-SignedHeaders=host&X-Goog-Signature=88662313af0f259c4eabd6b3ff5c49b2824cbd3c9bed40d7cfb594a78ef59150872ddfadee462487dfb60a116722b3e532565f8baebf0ad21ccce121e2fd9214f36ae949241bfc31bd92e0b687a9ea5eadebfa2b78d1a38c2d4d9b71817dbd309aca467c57fa662158f8186b725319cdf80fceb08ef82f8224766c05e482ac645177053a7ffcf2d17b194b8467c2c368e2eb4be78ce8bc96381f09a44b8a656e8c8bc69f97edf65c41689e42974da9fbde85a9780429868899964c1979a5f7465b2705b44b408e1ff6a458786e3a200bfe5568bc3b103679c3c85017261d16e2a8b00365ecb43f74dc036bb45f6f7a7c0204b2964dd5e979ff6a374c8a74a3ab'
    }
}
```

## Desired Behavior

### Display Requirements
1. **Visibility**: `file_link` messages should appear in the chat log when received in the stream response
2. **Presentation**: Similar to how `suggested_action` messages are displayed, but:
   - Smaller and more compact
   - Single line format
   - Clear indication that it's a clickable link
3. **Functionality**: The displayed link should be clickable and open the file URL

### Suggested Implementation Approach

The implementation should follow the existing pattern used for `suggested_action` messages:

1. **Message Handling**: Add a new case in the stream response handler to detect and process `file_link` messages

2. **UI Component**: Create a compact, single-line display component that shows:
   - A file icon or indicator
   - The decoded filename (URL decode the `name` field)
   - A clickable link to the URL
   
3. **Styling**: The component should:
   - Be visually distinct but not dominant
   - Use less vertical space than `suggested_action` messages
   - Clearly indicate it's a link (e.g., with underline, color, or icon)

### Example Display Format
```
📄 File: DSPIC33EP64GP504-E/PT.pdf [View]
```
or
```
🔗 DSPIC33EP64GP504-E/PT.pdf
```

## Implementation Checklist
- [ ] Add `file_link` message type handler in stream response processing
- [ ] Create compact UI component for displaying file links
- [ ] URL decode the filename for better readability
- [ ] Make the link clickable (opens in new tab)
- [ ] Style appropriately (single line, compact)
- [ ] Test with actual file_link messages from the API
- [ ] Ensure proper handling of special characters in filenames
- [ ] Verify pre-signed URLs work correctly

## Additional Considerations

1. **URL Decoding**: The filename may contain URL-encoded characters (e.g., `%2F` for `/`, `%2FPT` for `/PT`). Ensure proper decoding for display.

2. **Link Expiration**: Pre-signed URLs have an expiration time (shown in the example as 12 hours via `X-Goog-Expires=43200`). Consider:
   - Whether to show expiration time
   - How to handle expired links
   - Whether to cache or refresh the URL

3. **File Type Indication**: Consider showing a file type icon or extension for better UX

4. **Accessibility**: Ensure the link is keyboard accessible and has appropriate ARIA labels

## Reference
Look at the existing implementation of `suggested_action` message display for patterns and conventions to follow.
